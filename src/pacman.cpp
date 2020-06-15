#include "pacman.h"
#include <cmath>
#include <iostream>

void Pacman::Move(Direction direction) {
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
  this->direction = direction;
}

void Pacman::AnimateSprite() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 150) % 3; // alternate 3 sprites
  sprite.x = SPRITE_SIZE * animation_frame;
}
