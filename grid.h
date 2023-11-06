#pragma once

#include <istream>
#include <stdexcept>
#include <vector>

// NOTE: You do not need to understand this code in order to
// work on your solution, but feel free to snoop around if
// you are interested.

class Grid {
 public:
  // Constructors
  Grid(unsigned int num_rows, unsigned int num_cols);
  Grid(const Grid& g);

  // Grid size
  unsigned int num_rows() const;
  unsigned int num_cols() const;

  // Field accessors
  char& field(unsigned int row, unsigned int col);
  const char& field(unsigned int row, unsigned int col) const;

  // Vertical line accessors
  bool& vertical(unsigned int row, unsigned int col);
  const bool& vertical(unsigned int row, unsigned int col) const;

  // Horizontal line accessors
  bool& horizontal(unsigned int row, unsigned int col);
  const bool& horizontal(unsigned int row, unsigned int col) const;

  // Print the game state
  void print_grid() const;
  void print_grid(std::ostream& os) const;

 private:
  // std::vector<bool> works different from other std::vectors
  // A wrapper enables usual std::vector functionality
  struct boolWrap {
    bool value;
  };

  unsigned int m_num_rows;
  unsigned int m_num_cols;
  std::vector<char> m_fields;
  std::vector<boolWrap> m_vertical;
  std::vector<boolWrap> m_horizontal;
};