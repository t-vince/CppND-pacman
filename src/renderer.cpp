#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "ghost.h"

#define SPRITES_PATH "./assets/pacman_sprites.bmp"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      grid_width_(grid_width),
      grid_height_(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(IMG_INIT_PNG) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window_ = SDL_CreateWindow("Pac-Man Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize spritesheet
  SDL_Surface *_surfaceBMP = SDL_LoadBMP(SPRITES_PATH);
  spritesheet_ = SDL_CreateTextureFromSurface(sdl_renderer_, _surfaceBMP);
  if (nullptr == spritesheet_) {
    std::cerr << "Image cannot be loaded." << "\n";
    std::cerr << "IMG_Error: " << IMG_GetError() << "\n";
  }
  SDL_FreeSurface(_surfaceBMP);
}

Renderer::~Renderer() {
  SDL_DestroyTexture(spritesheet_);
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);

  spritesheet_ = nullptr;
  sdl_renderer_ = nullptr;
  sdl_window_ = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void Renderer::Render(Pacman const &pacman, 
                      std::vector<SDL_Point> const &food, 
                      Grid const &grid, 
                      std::vector<std::unique_ptr<Ghost>> const &ghosts) {
  SDL_Rect block;
  block.w = screen_width_ / grid_width_;
  block.h = screen_height_ / grid_height_;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render walls
  SDL_SetRenderDrawColor(sdl_renderer_, 0x16, 0x01, 0xF8, 0xFF);
  for (auto y = 0; y < grid_height_; y++) {
    for (auto x = 0; x < grid_width_; x++) {
      if (grid.HasWallAt(x, y)) {
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer_, &block);
      }
    }
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xCC, 0x00, 0xFF);
  SDL_Rect foodSquare{0, 0, 3, 3};
  for (auto const& f : food) {
    foodSquare.x = f.x * block.w + block.w / 2;
    foodSquare.y = f.y * block.h + block.h / 2;
    SDL_RenderFillRect(sdl_renderer_, &foodSquare);
  }

  // Render ghosts
  for (auto const &ghost : ghosts) {
    block.x = ghost->GetPosition().x * block.w;
    block.y = ghost->GetPosition().y * block.h;
    SDL_RenderCopy(sdl_renderer_, spritesheet_, &ghost->sprite, &block);
  }

  // Render pacman
  block.x = pacman.GetPosition().x * block.w;
  block.y = pacman.GetPosition().y * block.h;
  SDL_RenderCopy(sdl_renderer_, spritesheet_, &pacman.sprite, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Pac-Man Score: " + std::to_string(score) + " | FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}