#include "pacman.h"
#include <cmath>
#include <iostream>

// void Pacman::Update() {
//   SDL_Point prev_cell{
//       static_cast<int>(pos_x),
//       static_cast<int>(
//           pos_y)};
//   UpdatePos();
//   SDL_Point current_cell{
//       static_cast<int>(pos_x),
//       static_cast<int>(pos_y)}; 
// }

// void Pacman::UpdatePos() {
//   switch (direction) {
//     case Direction::Up:
//       pos_y -= speed_;
//       break;

//     case Direction::Down:
//       pos_y += speed_;
//       break;

//     case Direction::Left:
//       pos_x -= speed_;
//       break;

//     case Direction::Right:
//       pos_x += speed_;
//       break;
//   }

//   pos_x = fmod(pos_x + grid_width_, grid_width_);
//   pos_y = fmod(pos_y + grid_height_, grid_height_);
// }

void Pacman::Move(Direction direction) {
  this->direction = direction;
//   sprite.w = SPRITE_SIZE;
//   sprite.h = SPRITE_SIZE;
  switch (direction) {
    case Direction::Up:
      sprite.x = 0;
      sprite.y = SPRITE_SIZE * 2;
      break;

    case Direction::Down:
      sprite.x = 0;
      sprite.y = SPRITE_SIZE * 3;
      break;

    case Direction::Left:
      sprite.x = 0;
      sprite.y = 0;
      break;

    case Direction::Right:
      sprite.x = 0;
      sprite.y = SPRITE_SIZE;
      break;
  }
}

void Pacman::Update() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 100) % 3;
  sprite.x = SPRITE_SIZE * animation_frame;

  switch (direction) {
    case Direction::Up:
      pos_y -= speed_;
      break;

    case Direction::Down:
      pos_y += speed_;
      break;

    case Direction::Left:
      pos_x -= speed_;
      break;

    case Direction::Right:
      pos_x += speed_;
      break;
  }

  pos_x = fmod(pos_x + grid_width, grid_width);
  pos_y = fmod(pos_y + grid_height, grid_height);
  position.x = pos_x;
  position.y = pos_y;
}
