/**
   File to contain definition of board_t class along with additional
   data structures, constants required for board (chess)

   @author Suresh Golconda
*/

#ifndef KNIGHT_BOARD_H
#define KNIGHT_BOARD_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <climits>

#define MAX_EDGES 8

namespace knight_t
{

  //values from INT_MAX to INT_MAX - 5 reserved for special labels
  unsigned const int BLOCKED = INT_MAX;  // To mark cell as blocked
  unsigned const int WATER = (INT_MAX -1); // To mark cell as WATER
  unsigned const int ROCK = (INT_MAX - 2);  // To mark cell as ROCK
  unsigned const int BARRIER = (INT_MAX - 3); // To mark cell as BARRIER
  unsigned const int TELEPORT = (INT_MAX - 4); // To mark cell as TELEPORT
  unsigned const int LAVA = (INT_MAX - 5); // To mark cell as LAVA

  unsigned const KNIGHT_C = (INT_MAX -6);
  unsigned const int MIN_VALID_VALUE = (INT_MAX - 7);


  /// To store the index of a cell on the board
  struct cell_ind_t
  {
    int xi; // x-index, column-index. Origin (top left)
    int yi; // y-index, row -index
  };
  typedef std::vector<cell_ind_t> path_t;



  /// Used while storing a cell for path exploration
  struct cell_t
  {
    int value;
    int parent_xi;
    int parent_yi;
  };


  /**
     Class to contain check board configuration. It is initialized with
     DIM_SIZE, size of the chess board in one dimension.
  */
  class board_t
  {
    int DIM_SIZE;  //! size of each dimension (row/column)

    cell_t **m_cells;
    
    /// To store ths list of teleport cells
    std::vector<int> m_teleport_xi;
    std::vector<int> m_teleport_yi;

  public:

    /**
       Display board
    */
    void display_board();


    /**
       Display board with given move marked on it
    */
    void display_move(cell_ind_t const &move_);


    /** Display the board for each move */    
    void display_path(path_t const &moves_);


    /**
       Sets given arra of points as teleport cells
    */
    void set_teleport_cells(int teleport_xi_[], int teleport_yi_[]);


    /**
       @param dim_size_: dimension of the board
    */
    board_t(int dim_size_): DIM_SIZE (dim_size_)
    {
      // setup the board
      m_cells = new cell_t* [DIM_SIZE];
      for (int i=0; i< DIM_SIZE; i++)
	m_cells[i] = new cell_t [DIM_SIZE];

      // initialize board
      reset(0); 
    }

    /**
       Resets all the cells on the board with given value
    */
    void reset(int value_);


    /**
       Returns true if the given cell falls within the board
    */
    bool on_board(cell_ind_t const cell_)
    {
      return ((cell_.xi >= 0) && (cell_.xi <DIM_SIZE) &&
	      (cell_.yi >= 0) && (cell_.yi < DIM_SIZE));

    }

    /**
       Returns the value of the given cell (xi, yi)
    */
    int value (int xi, int yi)
    {
      return m_cells[xi][yi].value;
    }


    /**
       Sets the value and parent node for given cell
    */
    void set(int xi, int yi, int value, int parent_xi =-1, 
	     int parent_yi =-1)
    {
      m_cells[xi][yi].value = value;
      m_cells[xi][yi].parent_xi = parent_xi;
      m_cells[xi][yi].parent_yi = parent_yi;

      //automatically add the telport cells to a vector
      if (value == TELEPORT)
	{
	  m_teleport_xi.push_back (xi);
	  m_teleport_yi.push_back (yi);
	}
    }

    /**
       Returns reference to the cell at (xi, yi)
    */
    cell_t& get(int xi, int yi)
    {
      return m_cells[xi][yi];
    }


    /**
       Returns constant reference to vector of x coordinates of teleport cells.
    */
    std::vector<int> const& get_teleport_x()
    {
      return m_teleport_xi;
    }
    

    /**
       Returns constant reference to vector of y coordinates of teleport cells.
    */
    std::vector<int> const& get_teleport_y()
    {
      return m_teleport_yi;
    }


    /**
       Checks if the pair of given cells are one knight step away.
    */
    bool knight_neighbor (cell_ind_t const &c1, cell_ind_t const &c2)
    {
      int xdiff = c1.xi - c2.xi;
      int ydiff = c1.yi - c2.yi;
      
      if (((std::abs (xdiff) == 2) && std::abs (ydiff) == 1) ||
	  ((std::abs (xdiff) == 1) && std::abs (ydiff) == 2))
	return true;
      else
	return false;
    }


    /**
       Return true if points c1, c2 are both teleport points
    */
    bool teleport_points (cell_ind_t const &c1, cell_ind_t const &c2)
    {
      return ((m_cells[c1.xi][c1.yi].value == TELEPORT) &&
	      (m_cells[c2.xi][c2.yi].value == TELEPORT));
    }
    

    /**
       Returns true if sequence of points in path is valid knight
       moves and falls within the board.
    */
    bool check_valid_path(path_t const &path_, bool display_);

    ~board_t()
    {
      for (int i=0; i< DIM_SIZE; i++)
	delete [] m_cells[i];
      delete [] m_cells;
    }

  }; //end class board_t


}; // end namespace

#endif
