
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
        grid_width_(grid_width),
        grid_height_(grid_height)
         {
          //position.w = SPRITE_SIZE;
          //position.h = SPRITE_SIZE;
          sprite.w = SPRITE_SIZE;
          sprite.h = SPRITE_SIZE;
        }
  virtual ~Actor() {};

  void Update();
  void SetPosition(SDL_Point);
  virtual void UpdateSprite() = 0;
  virtual void Move(Direction direction) = 0;

  Direction direction = Direction::Up;

  int size{1};
  bool alive{true};
  SDL_Point position;
  SDL_Rect sprite;
  float speed_;

 private:
   float pos_x_{0.0};
   float pos_y_{0.0};
   int grid_width_;
   int grid_height_;
};

#endif