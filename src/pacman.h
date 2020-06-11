
#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "actor.h"
#include "SDL.h"

class Pacman : public Actor{
 public:
 // enum class Direction { kUp, kDown, kLeft, kRight };

  Pacman(int grid_width, int grid_height) : Actor(grid_width, grid_height, 0.1f) {}

  void Move(Direction direction) override;
  void Update() override;
//   void UpdatePos() override;
//   Direction direction = Direction::kUp;

//   float speed{0.1f};
//   int size{1};
//   bool alive{true};
//   float pos_x;
//   float pos_y;

 private:
//   void UpdatePos();

//   int grid_width;
//   int grid_height;
};

#endif