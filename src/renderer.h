
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "pacman.h"
#include "ghost.h"
#include "grid.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(const Renderer&&) = delete;

  void Render(Pacman const &pacman, 
              std::vector<SDL_Point> const &food, 
              Grid const &grid,
              std::vector<std::unique_ptr<Ghost>> const &ghosts);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window_ = nullptr;
  SDL_Renderer *sdl_renderer_ = nullptr;
  SDL_Texture *spritesheet_ = nullptr;

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
};

#endif