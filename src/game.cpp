#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <sstream>
#include "utilities.h"
#include "ghost.h"

using std::string;
using std::ifstream;
using std::istringstream;
using std::vector;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pacman_(grid_width, grid_height), engine(dev()) {

  ReadLevelFromFile("./assets/level-1.txt", grid_width, grid_height);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, pacman_);
    Update();
    renderer.Render(pacman_, food_, walls_, ghosts_);

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
}

void Game::Update() {
  if (!pacman_.alive) {
    std::cout << "Game Over" << "\n";
    std::cout << "Final score: " << GetScore() << "\n";
    return;
  }

  if (food_.empty()) {
    // Game finished, all food was eaten
    std::cout << "Congratz!" << "\n";
    std::cout << "Final score: " << GetScore() << "\n";
    return;
  }

  // Update position ghosts
  for (auto &ghost : ghosts_) {
    ghost->Update();
  }

  pacman_.Update();

  // int new_x = static_cast<int>(pacman_.pos_x);
  // int new_y = static_cast<int>(pacman_.pos_y);

  // Check if Pac-Man got eaten by a ghost
  for (auto &ghost : ghosts_) {
    if (ghost->position == pacman_.position) {
      pacman_.alive = false;
      break;
    }
  }
  
  // Check if Pac-Man ate food (if so, remove food and increase score)
  for(auto food = food_.begin(); food != food_.end();) {
    if (pacman_.position == *food) {
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
    point.y = 1;

    while (getline(level_file, line)) {
      istringstream sline(line);
      point.x = 0;

      while (sline >> c) {
        switch (c) {
          case '#':
            walls_.push_back(point);
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