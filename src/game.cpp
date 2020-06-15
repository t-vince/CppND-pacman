#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <sstream>
#include "utilities.h"
#include "ghost.h"
#include <thread>
#include <future>

using std::string;
using std::ifstream;
using std::istringstream;
using std::vector;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pacman_(grid_width, grid_height) {

  ReadLevelFromFile("./assets/level-1.txt", grid_width, grid_height);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, pacman_);
    Update();
    renderer.Render(pacman_, food_, grid_, ghosts_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  // Delay before closing the game
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Game::Update() {
  if (!pacman_.alive) return;

  if (food_.empty()) {
    // Game finished, all food was eaten
    std::cout << "\n" << "   ~ You win ~   " << "\n" << "\n";
    std::cout << "Final score: " << GetScore() << "\n";
    running = false;
    return;
  }

  // Update Pac-Man
  pacman_.Update(grid_);

  // Calculate next direction
  std::vector<std::thread> threads;
  std::vector<std::future<void>> futures;
  for (auto &ghost : ghosts_) {
    std::promise<void> prms;
    futures.emplace_back(prms.get_future());
    threads.emplace_back(&Ghost::CalculateNextMove, ghost.get(), std::ref(grid_), std::ref(pacman_), std::move(prms));
  }

  // wait for the results
  std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
      ftr.wait_for(std::chrono::milliseconds(100));
  });

  // Update position of ghosts
  for (auto &ghost : ghosts_) {
    ghost->Update(grid_);
  }

  // Check if Pac-Man got eaten by a ghost
  for (auto &ghost : ghosts_) {
    if (ghost->GetPosition() == pacman_.GetPosition()) {
      pacman_.alive = false;
      std::cout << "\n" << "   ~ Game Over ~   " << "\n" << "\n";
      std::cout << "Final score: " << GetScore() << "\n";
      running = false;
      break;
    }
  }

  // Thread barrier
  for (auto &t : threads) {
    if(t.joinable())
      t.join();
  }
  
  // Check if Pac-Man ate food (if so, remove food and increase score)
  for(auto food = food_.begin(); food != food_.end();) {
    if (pacman_.GetPosition() == *food) {
      score++;
      food_.erase(food);
    } else {
      food++;
    }
  }
}

int Game::GetScore() const { return score; }

void Game::ReadLevelFromFile(string level_path, std::size_t grid_width, std::size_t grid_height) {
  ifstream level_file (level_path);
  if (level_file) {
    string line;
    int ghost_count = 0;
    char c;
    SDL_Point point;
    point.y = 0;

    while (getline(level_file, line)) {
      istringstream sline(line);
      point.x = 0;
      while (sline >> c) {
        switch (c) {
          case '#':
            grid_.SetWallAt(point.x, point.y);
            break;

          case 'P':
            pacman_.SetPosition(point);
            break;

          case 'G':
            ghost_count++;
            ghosts_.emplace_back(std::make_unique<Ghost>(grid_width, grid_height, ghost_count, point));
            break;

          default:
            food_.push_back(point);
        }
        point.x++;
      }

      point.y++;
    }
    
  } else {
    throw std::invalid_argument("Level file does not exist");
  }
}