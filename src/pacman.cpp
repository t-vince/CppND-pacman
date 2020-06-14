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
  sprite.x = 0;
  switch (direction) {
    case Direction::Up:
      sprite.y = SPRITE_SIZE * 2;
      break;

    case Direction::Down:
      sprite.y = SPRITE_SIZE * 3;
      break;

    case Direction::Left:
      sprite.y = 0;
      break;

    case Direction::Right:
      sprite.y = SPRITE_SIZE;
      break;
  }
}

void Pacman::UpdateSprite() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 100) % 3;
  sprite.x = SPRITE_SIZE * animation_frame;
}
