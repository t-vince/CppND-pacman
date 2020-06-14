
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "SDL.h"

#define SPRITE_SIZE 20

class Actor {
 public:
  enum class Direction { Up, Down, Left, Right };

  Actor(int grid_width, int grid_height, float speed)
      : speed_(speed),
        grid_width(grid_width),
        grid_height(grid_height)
         {
          //position.w = SPRITE_SIZE;
          //position.h = SPRITE_SIZE;
          position.x = pos_x;
          position.x = pos_y;
          sprite.w = SPRITE_SIZE;
          sprite.h = SPRITE_SIZE;
        }
  virtual ~Actor() {};

  virtual void Update() = 0;
  virtual void Move(Direction direction) = 0;

  Direction direction = Direction::Up;

  int size{1};
  bool alive{true};
  float pos_x{0.0};
  float pos_y{0.0};
  SDL_Point position;
  SDL_Rect sprite;
  float speed_;

 protected:
   int grid_width;
   int grid_height;

 private:
};

#endif