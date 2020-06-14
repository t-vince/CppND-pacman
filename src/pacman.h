
#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "actor.h"
#include "SDL.h"

class Pacman : public Actor {
 public:
  Pacman(int grid_width, int grid_height) : Actor(grid_width, grid_height, 0.1f) {
    sprite.y = SPRITE_SIZE * 2;
  }
  ~Pacman() = default;

  void Move(Direction direction) override;
  void UpdateSprite() override;

 private:
};

#endif