#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "ghost.h"

#define SPRITES_PATH "./assets/pacman_sprites.bmp"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(IMG_INIT_PNG) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Pac-Man Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize spritesheet
//   spritesheet_ = SDL_LoadBMP("assets/pacman-sprites.png");
  
//   if (nullptr == spritesheet_) {
//     std::cerr << "Sprites could not be loaded.\n";
//     std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
//   }
  SDL_Surface *_surfaceBMP = SDL_LoadBMP(SPRITES_PATH);
  spritesheet_ = SDL_CreateTextureFromSurface(sdl_renderer, _surfaceBMP);
  //spritesheet_ = IMG_LoadTexture(sdl_renderer, SPRITES_PATH);
  if (nullptr == spritesheet_) {
        std::cerr << "image cannot load" << "\n";
        std::cerr << "IMG_Error: " << IMG_GetError() << "\n";
    }
}

Renderer::~Renderer() {
  //SDL_FreeSurface(spritesheet_);
  SDL_DestroyTexture(spritesheet_);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  IMG_Quit();
  SDL_Quit();
}

void Renderer::Render(Pacman const &pacman, 
                      std::vector<SDL_Point> const &food, 
                      std::vector<SDL_Point> const &walls, 
                      std::vector<std::unique_ptr<Ghost>> const &ghosts) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render walls
  SDL_SetRenderDrawColor(sdl_renderer, 0x16, 0x01, 0xF8, 0xFF);
  for (auto const& wall : walls) {
    block.x = wall.x * block.w;
    block.y = wall.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  SDL_Rect foodSquare{0, 0, 3, 3};
  for (auto const& f : food) {
    foodSquare.x = f.x * block.w + block.w / 2;
    foodSquare.y = f.y * block.h + block.h / 2;
    SDL_RenderFillRect(sdl_renderer, &foodSquare);
  }

  // Render ghosts
  for (auto const &ghost : ghosts) {
    block.x = ghost->GetPosition().x * block.w;
    block.y = ghost->GetPosition().y * block.h;
    SDL_RenderCopy(sdl_renderer, spritesheet_, &ghost->sprite, &block);
  }

  // Render pacman
  block.x = pacman.GetPosition().x * block.w;
  block.y = pacman.GetPosition().y * block.h;
  SDL_RenderCopy(sdl_renderer, spritesheet_, &pacman.sprite, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}