
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "SDL.h"

#define SPRITE_SIZE 20

class Actor {
 public:
  enum class Direction { Up, Down, Left, Right };

  Actor(int grid_width, int grid_height, float speed)
      : grid_width(grid_width),
        grid_height(grid_height),
        speed_(speed),
        pos_x(grid_width / 2),
        pos_y(grid_height / 2) {
          position.w = SPRITE_SIZE;
          position.h = SPRITE_SIZE;
          position.x = pos_x;
          position.x = pos_y;
          sprite.w = SPRITE_SIZE;
          sprite.h = SPRITE_SIZE;
        }

  virtual void Update() = 0;
  virtual void Move(Direction direction) = 0;

  Direction direction = Direction::Up;

  int size{1};
  bool alive{true};
  float pos_x;
  float pos_y;
  SDL_Rect position;
  SDL_Rect sprite;
  float speed_;

  int grid_width;
  int grid_height;

 private:
};

#endif