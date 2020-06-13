
#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include "actor.h"
#include "SDL.h"

class Ghost : public Actor{
 public:
 // enum class Direction { kUp, kDown, kLeft, kRight };

  Ghost(int grid_width, int grid_height, int ghost_number) : Actor(grid_width, grid_height, 0.1f), ghost_number_(ghost_number) {
      if (ghost_number_  > 4) throw std::invalid_argument("There can only be 4 ghosts");
  }

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
   const int ghost_number_;
//   void UpdatePos();

//   int grid_width;
//   int grid_height;
};

#endif