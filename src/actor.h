
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
        grid_height_(grid_height)
         {
          sprite.w = SPRITE_SIZE;
          sprite.h = SPRITE_SIZE;
        }
  virtual ~Actor() {};

  void Update(Grid const &grid);
  void SetPosition(SDL_Point);
  SDL_Point GetPosition() const;

  virtual void AnimateSprite() = 0;
  virtual void Move(Direction direction) = 0;

  Direction direction = Direction::Up;

  int size{1};
  bool alive{true};
  SDL_Rect sprite;
  float speed_;

 private:
   float pos_x_{0.0};
   float pos_y_{0.0};
   int grid_width_;
   int grid_height_;
};

#endif