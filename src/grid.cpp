#include "grid.h"

bool Grid::HasWallAt(int x, int y) const {
  return grid_[y][x];
}

void Grid::SetWallAt(int x, int y) {
  grid_[y][x] = true;
}