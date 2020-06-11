#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_image.h>

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

void Renderer::Render(Pacman const pacman, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render pacman
//   block.x = static_cast<int>(pacman.pos_x) * block.w;
//   block.y = static_cast<int>(pacman.pos_y) * block.h;
//   if (pacman.alive) {
//     SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   } else {
//     SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//   }
//  SDL_RenderFillRect(sdl_renderer, &block);
  //SDL_BlitSurface(spritesheet_, &pacman.sprite, sdl_window, *pacman.sprite);
  // SDL_Rect srcrect = { 0, 0, 17, 17 };
  // SDL_Rect dstrect = { 10, 10, 15, 15 };
  //std::cout << pacman.sprite.x << " " << pacman.sprite.y << " " << pacman.sprite.w << " " << pacman.sprite.h << "\n";
  //std::cout << pacman.position.x << " " << pacman.position.y << " " << pacman.position.w << " " << pacman.position.h << "\n";
  SDL_RenderCopy(sdl_renderer, spritesheet_, &pacman.sprite, &pacman.position);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}