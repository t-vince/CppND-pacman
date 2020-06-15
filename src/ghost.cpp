#include "ghost.h"
#include "pacman.h"
#include "grid.h"
#include "SDL.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <future>

void Ghost::CalculateNextMove(Grid const &grid, Pacman &pacman, std::promise<void>&& prms) {
  std::vector<Direction> directions{};

  auto current_position = GetPosition();
  auto pacman_position = pacman.GetPosition();

  if (CanMoveTo(direction, grid, current_position)) {
    if (rand() % 100 > (ghost_number_*5))
      return;
  }

  // Different ghosts have a different chance of making a more intelligent next-step decision
  if (rand() % 100 > (ghost_number_*10)) {
    if (pacman_position.x < current_position.x) {
      if (CanMoveTo(Direction::Left, grid, current_position)) {
        directions.push_back(Direction::Left);
      }
    } else {
      if (CanMoveTo(Direction::Right, grid, current_position)) {
        directions.push_back(Direction::Right);
      }
    }

    if (pacman_position.y < current_position.y) {
      if (CanMoveTo(Direction::Up, grid, current_position)) {
        directions.push_back(Direction::Up);
      }
    } else {
      if (CanMoveTo(Direction::Down, grid, current_position)) {
        directions.push_back(Direction::Down);
      }
    }
  }

  // If directions is still empty, either no possible were found or ghost was not intelligent enough
  if (directions.size() == 0) {
    if (CanMoveTo(Direction::Right, grid, current_position)) {
      directions.push_back(Direction::Right);
    }
    if (CanMoveTo(Direction::Left, grid, current_position)) {
      directions.push_back(Direction::Left);
    }
    if (CanMoveTo(Direction::Down, grid, current_position)) {
      directions.push_back(Direction::Down);
    }
    if (CanMoveTo(Direction::Up, grid, current_position)) {
      directions.push_back(Direction::Up);
    }
  }

  if (directions.size() == 0) {
    throw std::invalid_argument("Ghost is stuck");
  }

  Direction new_direction = directions.at(rand() % directions.size());

  // Only allow going back if it's the only option
  Direction opposite = GetOppositeDirection(direction);
  if (opposite == new_direction && directions.size() > 1) {
      new_direction = direction;
  }

  Move(std::move(new_direction));
  prms.set_value();
}

Actor::Direction Ghost::GetOppositeDirection(Direction const &direction) const {
  switch(direction) {
    case Direction::Up:
      return Direction::Down;
    case Direction::Down:
      return Direction::Up;
    case Direction::Left:
      return Direction::Right;
    case Direction::Right:
      return Direction::Left;
  }
}

bool Ghost::CanMoveTo(Direction const &direction, Grid const &grid, SDL_Point const &position) const {
  switch(direction) {
    case Direction::Up:
      return (!grid.HasWallAt(position.x, position.y - 1));
    case Direction::Down:
      return (!grid.HasWallAt(position.x, position.y + 1));
    case Direction::Left:
      return (!grid.HasWallAt(position.x - 1, position.y));
    case Direction::Right:
      return (!grid.HasWallAt(position.x + 1, position.y));
  }
}

void Ghost::Move(Direction direction) {
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
  this->direction = direction;
}

void Ghost::AnimateSprite() {
  Uint32 ticks = SDL_GetTicks();
  Uint32 animation_frame = (ticks / 150) % 2;
  sprite.x = SPRITE_SIZE * animation_frame;
}
