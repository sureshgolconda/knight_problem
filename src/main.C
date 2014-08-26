/** @mainpage Knight Path Problem: This is problem to find certain paths that a knight can follow.
    @author Suresh Golconda
    @par Description:

    *   - Presently system implements 4 (of 5) problems, labelled as 'level'. 

    *   - level-1:Write a function that accepts a sequence of moves and reports 
    whether the sequence contains only valid knight moves. It should also
    optionally print the state of the knight board to the terminal as shown
    above after each move. The current position should be marked with a 'K'.

    - Level 2: Compute a valid sequence of moves from a given start point to a given 
    end point.

    - Level 3: Compute a valid sequence of moves from a given start point to a 
    given end point in the fewest number of moves.

    - Level 4: Now repeat the Level 3 task for this 32x32 board. Also, modify
    your validator from Level 1 to check your solutions. This board has the 
    following additional rules:
    1) W[ater] squares count as two moves when a piece lands there
    2) R[ock] squares cannot be used
    3) B[arrier] squares cannot be used AND cannot lie in the path
    4) T[eleport] squares instantly move you from one T to the other in 
    the same move
    5) L[ava] squares count as five moves when a piece lands there

    @par More information:
    - Please read the README file for more information on how to compile, run, etc.
    */
                

#include <csignal>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "board.H"
#include "search_path.H"
#include "util.H"

using namespace knight_t;
using namespace std;

char const *progname;
bool const m_debug = false;

void print_usage ()
{
  cout << "Usage: " <<progname <<"\n"
       << "\t[-v]\t To verify if input path is valid knight path\n"
       << "\t[-s]\t To find the shortest path from source to destination\n"
       << "\t[-b filename]\t Board diagram file\n"
       << endl;
  cout <<"Please refer README file for more information, and scripts folder for example usage" <<endl;
}
/**
    Function to capture input stream and scan for board dimension and
    path entries (array of (x,y) points. It then checks to make sure
    if the path is valid. Checks for path to fall within board, and is
    a valid step for knight.

    @return TRUE if valid, else returns FALSE
*/
void verify_input_stream_path()
{
  /// ---- capture input and parse
  string line;
  getline (cin, line);

  int dim_size;
  path_t path;


  /// --- scan input for board dimesnion nad path 
  if (!scan_path_string (line, dim_size, path))
    {
      printf("Error parsing input stream\n");
      return;
    }


  /// ---- Printing captured data
  printf("INPUT: board size=%d, path length: %lu\n", 
	 dim_size, path.size());

  for (int i=0; i< path.size(); i++)
    printf("(%d, %d) ", path[i].xi, path[i].yi);
  printf("\n");



  /// --- check if input path is valid
  board_t brd (dim_size);
  if (brd.check_valid_path(path, true))
    {
      printf("Input path: VALID\n");
    }
  else
    printf("Input path: NOT VALID\n");




  /// --- Display path on board
  printf("Alternative display of path: as numbers on the board\n");
  display_path_on_board(path, dim_size);
}

void run_shortest_path(int DIM_SIZE, cell_ind_t const &src, 
		       cell_ind_t const &dest, string board_diagram_file_)
{
  printf("Source (%d %d), destination (%d %d), dimensions=%d\n",
	 src.xi, src.yi, dest.xi, dest.yi, DIM_SIZE);


  board_t base_board(DIM_SIZE);
  if (! board_diagram_file_.empty())
    scan_board_diagram(board_diagram_file_, base_board,
		       DIM_SIZE);

  search_path_t sp(DIM_SIZE, &base_board, m_debug);
  path_t path;
  if (!sp.get_path(src.xi, src.yi, dest.xi, dest.yi, path))
    printf("NO PATH FOUND\n");
  else
    { // Path found
      printf("Path as numbers on the board\n");
      display_path_on_board(path, DIM_SIZE);

      if (base_board.check_valid_path (path, false))
	printf("Path validation: VALID PATH (using procedure from level-1)\n");
      else
	printf("Path Validation: NOT VALID\n");
    }
  if (! board_diagram_file_.empty())
    {
      printf("Base board\n");
      base_board.display_board();
    }

}


int main (int argc_, char **argv_)
{

  int opt;
  bool usage_error = false;
  progname = basename (argv_[0]);

  int task_to_perform = -1;
  int const TASK_VERIFY_PATH = 1;
  int const TASK_SEARCH_PATH = 2;

  // bool prob_verify_path =false;
  // bool prob_shortest_path = false;
  string board_diagram_file = "";



  while ((opt = getopt (argc_, argv_, "vsb:?")) != -1)
    switch (opt)
      {
      case 'v': // verify a given path is valid
	task_to_perform = TASK_VERIFY_PATH;
	//prob_verify_path = true;
	break;
      case 's': // shortest path
	task_to_perform = TASK_SEARCH_PATH;
	//prob_shortest_path = true;
	break;
      case 'b': //board diagram file
	board_diagram_file = optarg;
	break;
      default:
	usage_error = true;
	break;
      }

  if (usage_error)
    {
      print_usage();
      return 1;
    }

  switch (task_to_perform)
    {
    case TASK_VERIFY_PATH:
      verify_input_stream_path();
      break;

    case TASK_SEARCH_PATH:
      {
	/// read input stream for DIM_SIZE and start, dest
	string line;
	int dim_size =0;
	cell_ind_t src;
	cell_ind_t dest;
	getline (cin, line); /// read input stream

	///scan for parameters
	if (scan_dim_src_dest (line, dim_size, src, dest))
	  { 
	    run_shortest_path(dim_size, src, dest, board_diagram_file);	  
	  }
	else
	  printf("Error parsing input stream\n");      
      }
      break;

    default:
      usage_error = true;
      break;

    }

  if (usage_error)
    {
      print_usage();
      return 1;
    }
  return 0;
}
