
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "SDL.h"
#include "grid.h"

#define SPRITE_SIZE 20

class Actor {
 public:
  enum class Direction { Up, Down, Left, Right };

  Actor(int grid_width, int grid_height, float speed)
      : speed_(speed),
        grid_width_(grid_width),
        grid_height_(grid_height) {}
  virtual ~Actor() {};

  void Update(Grid const &grid);
  void SetPosition(SDL_Point);
  SDL_Point GetPosition() const;

  virtual void AnimateSprite() = 0;
  virtual void Move(Direction direction) = 0;

  Direction direction = Direction::Up;
  SDL_Rect sprite{0, 0, SPRITE_SIZE, SPRITE_SIZE};
  
 private:
   float speed_;
   float pos_x_{0.0};
   float pos_y_{0.0};
   int grid_width_;
   int grid_height_;
};

#endif