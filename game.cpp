#include "game.h"

#include <assert.h>

#include <iostream>

// Checks whether or not the game is finished.
// A game is considered finished when all lines have been drawn.
bool game_is_finished(const Grid& grid) {
  // TODO: Check all horizontal and vertical lines. (check)
  
  //vertical lines i-> 0,1 ; j-> 0,1,2
  for(unsigned int i=0; i<=grid.num_rows()-1; ++i){     
    for(unsigned int j=0; j<=grid.num_cols(); ++j){
      if(grid.vertical(i,j)==true){
        continue;
      } else {
        return false;
      }
    }
  }
  //horizontal lines i-> 0,1,2 ; j-> 0,1
  for(unsigned int i = 0; i<=grid.num_rows(); ++i){
    for(unsigned int j = 0; j<=grid.num_cols()-1; ++j){
      if(grid.horizontal(i,j)==true){
        continue;
      } else {
        return false;
      }
    }
  }
  return true;
  
  
}

// Draw a line in the grid starting at point (row, col) going towards the given
// direction
void draw_line(Grid& grid, unsigned int row, unsigned int col, char direction) {
  switch (direction) {
    case 'r':
      grid.horizontal(row, col) = true;
      break;
    case 'd':
      grid.vertical(row, col) = true;
      break;
    // TODO: Are there any additional directions that need to be handled? (check)
    case 'l':
      grid.horizontal(row, col - 1) = true;
      break;
    case 'u':
      grid.vertical(row - 1,col) = true;
      break;
    default:
      // We should never reach this point.
      std::cout << "Invalid line direction.";
      assert(false);
  }
}

// Checks whether or not a box (or field) is newly completed.
// A box is newly completed if all four sides are drawn but the box is not
// claimed yet.
bool is_newly_completed_box(const Grid& grid, unsigned int row,
                            unsigned int col) {
  // TODO: Check whether box is newly completed. 
  
  bool top = grid.horizontal(row,col);
  bool bottom = grid.horizontal(row + 1,col);
  bool right = grid.vertical(row,col + 1);
  bool left = grid.vertical(row,col);
  
  return top && bottom && right && left;
}




// Play the players move.
// This function returns true if the player completed a box with their move.
// Otherwise it returns false.
bool play_move(Grid& grid, char player, unsigned int row, unsigned int col,
               char direction) {
  // Note: we assume the move is valid
  // draw the new line
  draw_line(grid, row, col, direction);

  // check if the current players move completed a new box
  // Note: we assume the move is in right or down direction
  bool completed_new_box = false;
  
  if(direction == 'l'){
    direction = 'r';
    col -= 1;
  }
  if(direction == 'u'){
    direction = 'd';
    row -= 1;
  }
  
  switch (direction) {
    case 'r':
      // we drew a horizontal line

      // check if box above the horizontal line is newly completed
      // Note: box above only exists if the line is not at the top edge of
      // the grid!
    
      if (row > 0 && is_newly_completed_box(grid, row - 1, col)) {
        completed_new_box = true;
        grid.field(row - 1, col) = player;
      }
      // TODO: check box below horizontal line (check)
      if (row < grid.num_rows() && is_newly_completed_box(grid, row, col)) {
        completed_new_box = true;
        grid.field(row, col) = player;
      }
      break;
      
    // TODO: handle additional cases
    case 'd':
      //Die Linie links davon
      if (col > 0 && is_newly_completed_box(grid, row, col - 1)) {
        completed_new_box = true;
        grid.field(row, col - 1) = player;
      }

      //Die Linie rechts davon
      if (col < grid.num_cols() && is_newly_completed_box(grid, row, col)) {
        completed_new_box = true;
        grid.field(row, col) = player;
      }
      break;
  }

  return completed_new_box;
}

// Computes a players score.
// A Players score is the number of fields claimed by the player.
unsigned int compute_player_score(const Grid& grid, char player) {
  // TODO: Compute score of player.
  int score = 0;
    for (unsigned int row = 0; row < grid.num_rows(); ++row) {
        for (unsigned int col = 0; col < grid.num_cols(); ++col) {
            if (grid.field(row, col) == player) ++score;
        }
    }
  return score;
}

// Checks if the move is within the bounds of the grid,
// and the line is not already drawn
bool is_valid_move(const Grid& grid, unsigned int row, unsigned int col,
                   char direction) {
  // TODO: check whether or not the move is valid.
  
  switch (direction) {
        case 'u':
            return row > 0 && row <= grid.num_rows() && col >= 0 &&
                   col <= grid.num_cols() && !grid.vertical(row - 1, col);
        case 'd':
            return row >= 0 && row < grid.num_rows() && col >= 0 &&
                   col <= grid.num_cols() && !grid.vertical(row, col);
        case 'l':
            return row >= 0 && row <= grid.num_rows() && col > 0 &&
                   col <= grid.num_cols() && !grid.horizontal(row, col - 1);
        case 'r':
            return row >= 0 && row <= grid.num_rows() && col >= 0 &&
                   col < grid.num_cols() && !grid.horizontal(row, col);
        default:
            return false;
    }
}

// Main game loop
void play_game(Grid& grid) {
  // initialize player and step
  char current_player = 'A';
  unsigned int current_move = 1;

  // print initial grid
  grid.print_grid();

  // initialize user input
  unsigned int row, col;
  char direction;

  // loop while game is not finished
  while (!game_is_finished(grid)) {
    std::cout << "Move # " << current_move << std::endl;

    // get a valid move
    std::cout << "Player " << current_player << "'s move: ";
    std::cin >> row >> col >> direction;
    
    while (!is_valid_move(grid, row, col, direction)) {
      std::cout << "Invalid move!" << std::endl;
      std::cin >> row >> col >> direction;
    }
    
    // play the move
    bool move_completed_box =
        play_move(grid, current_player, row, col, direction);
    current_move += 1;

    // print grid
    grid.print_grid();

    // change current player
    // TODO: finish the player switching logic
    switch (current_player) {
      case 'A':
        if(move_completed_box == false){
          current_player = 'B';
        } else 
        current_player = 'A';
        break;
      case 'B':
        if(move_completed_box == false){
          current_player = 'A';
        } else 
        current_player = 'B';
        break;
      default:
        // We should never reach this point.
        std::cout << "Unknown Player";
        assert(false);
    }
  }

  // Game loop exited. The game must be finished
  std::cout << "Game finished" << std::endl;

  // Compute and display player scores
  unsigned int score_a = compute_player_score(grid, 'A');
  unsigned int score_b = compute_player_score(grid, 'B');
  std::cout << "Player A: " << score_a << std::endl;
  std::cout << "Player B: " << score_b << std::endl;
  if (score_a == score_b) {
    std::cout << "It's a draw!" << std::endl;
  } else {
    char winner = (score_a > score_b) ? 'A' : 'B';
    std::cout << "Player " << winner << " wins!" << std::endl;
  }
}