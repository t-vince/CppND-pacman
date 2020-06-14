
#ifndef GRID_H
#define GRID_H

// Game grid
class Grid {
 public:
  bool HasWallAt(int x, int y) const;
  void SetWallAt(int x, int y);

 private:
   bool grid_[20][20] = {{0}};
};

#endif