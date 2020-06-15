
#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include <future>
#include "actor.h"
#include "grid.h"
#include "pacman.h"
#include "SDL.h"

class Ghost : public Actor{
 public:
  Ghost(int grid_width, int grid_height, int ghost_number, SDL_Point point) : Actor(grid_width, grid_height, 0.1f), ghost_number_(ghost_number) {
      if (ghost_number_  > 4) throw std::invalid_argument("There can only be 4 ghosts");
      this->SetPosition(point);
      sprite.y = SPRITE_SIZE * (3 + ghost_number_);
      sprite.x = 0;
  }
  ~Ghost() = default;

  void CalculateNextMove(Grid const &grid, Pacman &pacman, std::promise<void>&& prms);
  void Move(Direction direction) override;
  void AnimateSprite() override;

 private:
   Direction GetOppositeDirection(Direction direction);
   bool CanMove(Direction const &direction, Grid const &grid, SDL_Point const &position);
   const int ghost_number_;
};

#endif