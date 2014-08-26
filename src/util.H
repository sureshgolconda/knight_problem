/**
   File to contain utility functions.
   @author Suresh Golconda
 */

#ifndef KNIGHT_UTIL_H
#define KNIGHT_UTIL_H

#include "board.H"
#include <string>
namespace knight_t
{
  /**
      Utility function for testing sample board configuration in a 8x8
      board
   */
  void set_board_cost_8x8(board_t &board_);


  /**
      Utility function for testing sample board configuration in a 16x16
      board
   */
  void set_board_cost_16x16(board_t &board_);


  /**
      Utility function for testing sample board configuration in a 32x32
      board
   */
  void set_board_cost_32x32(board_t &board_);


  /**
      Display the given path, on the board, by numbering the cells
      along the path.
   */
  void display_path_on_board(path_t const &path_, int dim_size_);


  /**
      Utility function to read the input board_diagram file and mark,
      given board with respective cells of {water, rock, barrier,
      teleport, lava}
   */
  void scan_board_diagram(std::string filePath_, board_t &brd_,
			  int DIM_SIZE_);

  /**
      Utility function to scan given string for sequence of points
      along the path.
   */
  bool scan_path_string (std::string indata_, int &dim_size_, path_t &path_);


  /**
      Utility function to scan, board's dimension, src, and
      destination cell information from given string.
   */
  bool scan_dim_src_dest (std::string indata_, int &dim_size_,
			  cell_ind_t &src_, cell_ind_t &dest_);

};

#endif
