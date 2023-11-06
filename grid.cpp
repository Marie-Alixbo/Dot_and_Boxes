#include "grid.h"

#include <iostream>
#include <sstream>
#include <string>

int count_digits(int n) {
  unsigned int d = 1;
  while (n > 9) {
    d++;
    n /= 10;
  }
  return d;
}

char get_digit(int n, int d) {
  while (d > 0) {
    n /= 10;
    d--;
  }
  return std::to_string(n % 10)[0];
}

Grid::Grid(unsigned int num_rows, unsigned int num_cols)
    : m_num_rows(num_rows), m_num_cols(num_cols) {
  m_fields.resize(num_rows * num_cols, ' ');
  m_vertical.resize(num_rows * (num_cols + 1), {false});
  m_horizontal.resize((num_rows + 1) * num_cols, {false});
}

Grid::Grid(const Grid& g) : m_num_rows(g.num_rows()), m_num_cols(g.num_cols()) {
  m_fields = std::vector<char>(g.m_fields);
  m_vertical = std::vector<boolWrap>(g.m_vertical);
  m_horizontal = std::vector<boolWrap>(g.m_horizontal);
}

unsigned int Grid::num_rows() const { return m_num_rows; }
unsigned int Grid::num_cols() const { return m_num_cols; }

char& Grid::field(unsigned int row, unsigned int col) {
  if (row < 0 || row >= m_num_rows || col < 0 || col >= m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_fields[row * m_num_cols + col];
}
const char& Grid::field(unsigned int row, unsigned int col) const {
  if (row < 0 || row >= m_num_rows || col < 0 || col >= m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_fields[row * m_num_cols + col];
}

bool& Grid::vertical(unsigned int row, unsigned int col) {
  if (row < 0 || row >= m_num_rows || col < 0 || col > m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_vertical[row * (m_num_cols + 1) + col].value;
}
const bool& Grid::vertical(unsigned int row, unsigned int col) const {
  if (row < 0 || row >= m_num_rows || col < 0 || col > m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_vertical[row * (m_num_cols + 1) + col].value;
}

bool& Grid::horizontal(unsigned int row, unsigned int col) {
  if (row < 0 || row > m_num_rows || col < 0 || col >= m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_horizontal[row * m_num_cols + col].value;
}
const bool& Grid::horizontal(unsigned int row, unsigned int col) const {
  if (row < 0 || row > m_num_rows || col < 0 || col >= m_num_cols) {
    throw std::runtime_error{"Invalid board position."};
  }
  return m_horizontal[row * m_num_cols + col].value;
}

void Grid::print_grid() const {
  std::stringstream ss;
  print_grid(ss);
  std::cout << ss.str();
}

void Grid::print_grid(std::ostream& os) const {
  int n_digits = std::max(count_digits(m_num_rows), count_digits(m_num_cols));

  // print header
  for (int d = n_digits - 1; d >= 0; d--) {
    // empty space for rows column
    for (int j = 0; j < n_digits; ++j) {
      os << ' ';
    }

    // current digit of column header
    for (unsigned int j = 0; j <= m_num_cols; ++j) {
      os << (count_digits(j) > d ? get_digit(j, d) : ' ') << ' ';
    }

    // end of row
    os << std::endl;
  }

  // print rows
  for (unsigned int i = 0; i <= m_num_rows; ++i) {
    // row id leading zeros (zeros are empty space)
    for (int j = count_digits(i); j < n_digits; ++j) {
      os << " ";
    }

    // row id
    os << i;

    // grid points and horizontal lines
    for (unsigned int j = 0; j < m_num_cols; ++j) {
      // grid point
      os << ".";

      // horizontal line
      os << (horizontal(i, j) ? "—" : " ");
    }
    os << "." << std::endl;

    // leading empty space for vertical lines
    for (int j = 0; j < n_digits; ++j) {
      os << " ";
    }

    // vertial lines and fields
    if (i < m_num_rows) {
      for (unsigned int j = 0; j <= m_num_cols; ++j) {
        os << (vertical(i, j) ? "|" : " ");

        if (j < m_num_cols) {
          os << field(i, j);
        }
      }
    }
    os << std::endl;
  }
}