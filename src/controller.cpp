#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "pacman.h"

void Controller::ChangeDirection(Pacman &pacman, Pacman::Direction input) const {
  pacman.Move(std::move(input));
  return;
}

void Controller::HandleInput(bool &running, Pacman &pacman) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(pacman, Pacman::Direction::Up);
          break;

        case SDLK_DOWN:
          ChangeDirection(pacman, Pacman::Direction::Down);
          break;

        case SDLK_LEFT:
          ChangeDirection(pacman, Pacman::Direction::Left);
          break;

        case SDLK_RIGHT:
          ChangeDirection(pacman, Pacman::Direction::Right);
          break;
      }
    }
  }
}