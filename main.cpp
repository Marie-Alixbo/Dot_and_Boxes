#include <iostream>
#include <sstream>
#include <string>

#include "game.h"
#include "grid.h"

int main() {
  // get user input for grid size
  std::cout << "Grid size: ";
  std::string grid_size;
  std::getline(std::cin, grid_size);

  // assume grid size is 2x2
  unsigned int n_rows = 2;
  unsigned int n_cols = 2;

  // change grid size if user entered non-empty line
  if (grid_size.length() != 0) {
    std::istringstream grid_size_iss(grid_size);
    grid_size_iss >> n_rows >> n_cols;
  }

  // init grid
  Grid grid(n_rows, n_cols);

  // start game
  play_game(grid);

  return 0;
}
