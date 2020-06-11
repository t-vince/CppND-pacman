#include "pacman.h"
#include <cmath>
#include <iostream>

void Pacman::Update() {
  SDL_Point prev_cell{
      static_cast<int>(pos_x),
      static_cast<int>(
          pos_y)};
  UpdatePos();
  SDL_Point current_cell{
      static_cast<int>(pos_x),
      static_cast<int>(pos_y)}; 
}

void Pacman::UpdatePos() {
  switch (direction) {
    case Direction::kUp:
      pos_y -= speed;
      break;

    case Direction::kDown:
      pos_y += speed;
      break;

    case Direction::kLeft:
      pos_x -= speed;
      break;

    case Direction::kRight:
      pos_x += speed;
      break;
  }

  pos_x = fmod(pos_x + grid_width, grid_width);
  pos_y = fmod(pos_y + grid_height, grid_height);
}
