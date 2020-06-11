#include "actor.h"
#include "SDL.h"

// void Actor::Move(Direction direction) {
//   direction = direction;
//   switch (direction) {
//     case Direction::Up:
//       sprite.x = 100;
//       sprite.y = 100;
//       break;

//     case Direction::Down:
//       sprite.x = 100;
//       sprite.y = 110;
//       break;

//     case Direction::Left:
//       sprite.x = 100;
//       sprite.y = 120;
//       break;

//     case Direction::Right:
//       sprite.x = 100;
//       sprite.y = 130;
//       break;
//   }
// }

// void Actor::Update() {
//   switch (direction) {
//     case Direction::Up:
//       pos_y -= speed_;
//       break;

//     case Direction::Down:
//       pos_y += speed_;
//       break;

//     case Direction::Left:
//       pos_x -= speed_;
//       break;

//     case Direction::Right:
//       pos_x += speed_;
//       break;
//   }

//   pos_x = fmod(pos_x + grid_width_, grid_width_);
//   pos_y = fmod(pos_y + grid_height_, grid_height_);
// }

// void Actor::Update() {
//   switch (direction) {
//     case Direction::Up:
//       pos_y -= speed_;
//       break;

//     case Direction::Down:
//       pos_y += speed_;
//       break;

//     case Direction::Left:
//       pos_x -= speed_;
//       break;

//     case Direction::Right:
//       pos_x += speed_;
//       break;
//   }

//   pos_x = fmod(pos_x + grid_width_, grid_width_);
//   pos_y = fmod(pos_y + grid_height_, grid_height_);
// }

