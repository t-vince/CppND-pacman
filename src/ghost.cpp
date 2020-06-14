#include "ghost.h"
#include <cmath>
#include <iostream>

void Ghost::Move(Direction direction) {
  this->direction = direction;
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

void Ghost::UpdateSprite() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 100) % 2;
  sprite.x = SPRITE_SIZE * animation_frame;
}
