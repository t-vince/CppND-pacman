
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "pacman.h"
#include "ghost.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Pacman const &pacman, 
              std::vector<SDL_Point> const &food, 
              std::vector<SDL_Point> const &walls,
              std::vector<std::unique_ptr<Ghost>> const &ghosts);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *spritesheet_ = NULL;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif