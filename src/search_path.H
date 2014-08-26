/**
   File to contain definition of search_path_t class along with
   additional constants required for the search operation

    @author Suresh Golconda
 */


#ifndef KNIGHT_SEARCH_PATH_H
#define KNIGHT_SEARCH_PATH_H

#include <climits>
#include <vector>
#include <queue>

#include "board.H"

#define NUM_NEIGHBORS 8

namespace knight_t
{

  /**
      Class to implement exploration of the chess board to find
      shortest path from given source cell to given destination cell.
   */
  class search_path_t
  {
    bool m_debug; /// set to true if required to print debug info
    unsigned short DIM_SIZE; /// size of each dimension (row/column)
    unsigned short NUM_CELLS;

    static unsigned const int WATER_COST = 2;
    static unsigned const int LAVA_COST = 5;

    board_t *m_base_board;

    /// inter mediate steps between knight's single move
    struct intermediate_steps_t
    {
      int dx[2];
      int dy[2];
      intermediate_steps_t (int dx1_, int dy1_, int dx2_, int dy2_)
      {
	dx[0] = dx1_;
	dy[0] = dy1_;
	dx[1] = dx2_;
	dy[1] = dy2_;
      }
    };


    /**
	Class to store a node for graph exploration.
     */
    class node_t
    {
    public:

      int xi; //todo: can replace with SHORT
      int yi;
      int pxi; //useful especially for teleportation
      int pyi;
      int value;

      node_t(int xi_, int yi_, int pxi_, int pyi_)
      { xi =xi_;
	yi =yi_;
	pxi = pxi_;
	pyi = pyi_;
	value = INT_MAX;
      }

      /**
	  Required for priority queue
       */
      bool operator < (node_t const &sn_) const
      {
	//return (value < sn_.value);
	return (sn_.value < value);
      };


      /**
	  To be able to compare node variables as (n1 == n2)
       */
      bool operator == (node_t const &sn_) const
      {
	return (sn_.xi == xi) && (sn_.yi == yi);
      };
    };


  public:
    /**
	@param debug_ if set will print additional debug information.
	debug_ parameter is option, is by default taken as false.
     */
    search_path_t (unsigned dim_size_, board_t *base_board_, 
		   bool debug_ = false): 
      DIM_SIZE (dim_size_)
    {
      m_base_board = base_board_;
      m_debug = debug_;
    }

    /**
	Returns the cost for neighbor cell when traversing from nd.
    */
    int new_cost (const node_t &nd, int nxi, int nyi);


    /**
       Return true if the path blocked by barrier. Else returns false.
    */
    bool move_blocked (const node_t &nd, intermediate_steps_t const* path);


    /**
	Implements the Best-First-Search for finding a path from
	(sx_i,syi_) to (exi_, eyi_).
	Reference: http://en.wikipedia.org/wiki/Best-first_search
     */
    bool get_path (int sxi_, int syi_, int exi_, int eyi_, path_t &path_);


    /**
	Traces the path from dest to source, to extract sequence of cells (path)
     */
    void trace_path(node_t const &dest, node_t const &src,
		    board_t &search_bd, path_t &path_);

    /**
	Marks the other end of teleport cell with equal cost and adds
	to exploration list.
     */
    void set_teleport_nav(node_t const &nd, board_t &search_bd,
			  std::priority_queue<node_t> &pq);

    /**
	Return the 2 intermediate (adjacent) steps in one step of knigh
    */
    intermediate_steps_t const* move_intersteps(int delx, int dely);

    /**
	Prints the intermediate cells of a knight's single step
     */
    void display_step_path(intermediate_steps_t const *path_)
    {
      printf("(%d, %d), (%d, %d)\n", path_->dx[0], path_->dy[0],
	     path_->dx[1], path_->dy[1]);
    }

  };
};

#endif
