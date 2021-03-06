#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "pacman.h"
#include "ghost.h"
#include "grid.h"

using std::vector;

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:
  bool running = true;
  Pacman pacman_;
  vector<std::unique_ptr<Ghost>> ghosts_;
  Grid grid_;
  vector<SDL_Point> food_;
  int score{0};

  void Update();
  void ReadLevelFromFile(std::string file, std::size_t grid_width, std::size_t grid_height);
};

#endif