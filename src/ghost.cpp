#include "ghost.h"
#include <cmath>
#include <iostream>

void Ghost::Move(Direction direction) {
  this->direction = direction;
  sprite.y = SPRITE_SIZE * (5 + ghost_number_);
  switch (direction) {
    case Direction::Up:
      sprite.x = 0;
      break;

    case Direction::Down:
      sprite.x = SPRITE_SIZE * 2;
      break;

    case Direction::Left:
      sprite.x = SPRITE_SIZE * 4;
      break;

    case Direction::Right:
      sprite.x = SPRITE_SIZE * 6;
      break;
  }
}

void Ghost::Update() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 100) % 2;
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
