#include "actor.h"
#include "SDL.h"
#include "utilities.h"
#include "grid.h"

void Actor::Update(Grid const &grid) {
  this->AnimateSprite();

  SDL_Point old_position{static_cast<int>(pos_x_), static_cast<int>(pos_y_)};

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

  // When going trough the side of the map, re-appear on the other side
  pos_x_ = fmod(pos_x_ + grid_width_, grid_width_);
  pos_y_ = fmod(pos_y_ + grid_height_, grid_height_);

  // If actor hits a wall, he's stading still
  if (grid.HasWallAt(pos_x_, pos_y_)) {
    pos_x_ = old_position.x;
    pos_y_ = old_position.y;
  }
}

void Actor::SetPosition(SDL_Point point) {
    pos_x_ = point.x;
    pos_y_ = point.y;
}

SDL_Point Actor::GetPosition() const {
    return SDL_Point{static_cast<int>(pos_x_), static_cast<int>(pos_y_)};
}
