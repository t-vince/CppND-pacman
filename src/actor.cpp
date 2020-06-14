#include "actor.h"
#include "SDL.h"

void Actor::Update() {
  this->UpdateSprite();

  switch (direction) {
    case Direction::Up:
      pos_y_ -= speed_;
      break;

    case Direction::Down:
      pos_y_ += speed_;
      break;

    case Direction::Left:
      pos_x_ -= speed_;
      break;

    case Direction::Right:
      pos_x_ += speed_;
      break;
  }

  pos_x_ = fmod(pos_x_ + grid_width_, grid_width_);
  pos_y_ = fmod(pos_y_ + grid_height_, grid_height_);
  position.x = pos_x_;
  position.y = pos_y_;
}

void Actor::SetPosition(SDL_Point point) {
    position = point;
    pos_x_ = point.x;
    pos_y_ = point.y;
}
