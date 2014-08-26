#include "util.H"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace knight_t;
using namespace std;


void knight_t::set_board_cost_8x8(board_t &board_)
{
  board_.reset(0); // set all cells to 0

  int water_xi[] = {2, 2, 2};
  int water_yi[] = {0, 1, 2};

  int rock_xi[] = {4, 4, 4};
  int rock_yi[] = {4, 5, 6};

  int barrier_xi[] = {5, 5, 5};
  int barrier_yi[] = {0, 1, 2};

  int teleport_xi[2] = {0, 1};
  int teleport_yi[2] = {7, 2};

  int lava_xi[] = {6, 6, 6};
  int lava_yi[] = {0, 1, 2};

  for (int i=0; i< (sizeof (water_xi)/sizeof (int)); i++)
    board_.set (water_xi[i], water_yi[i], WATER);

  for (int i=0; i< (sizeof (rock_xi)/sizeof (int)); i++)
    board_.set (rock_xi[i], rock_yi[i], ROCK);

  for (int i=0; i< (sizeof (barrier_xi)/sizeof (int)); i++)
    board_.set (barrier_xi[i], barrier_yi[i], BARRIER);

  for (int i=0; i< (sizeof (teleport_xi)/sizeof (int)); i++)
    board_.set (teleport_xi[i], teleport_yi[i], TELEPORT);

  for (int i=0; i< (sizeof (lava_xi)/sizeof (int)); i++)
    board_.set (lava_xi[i], lava_yi[i], LAVA);


}

void knight_t::set_board_cost_16x16(board_t &board_)
{
  board_.reset(0); // set all cells to 0

  int water_xi[] = {2, 2, 2};
  int water_yi[] = {0, 1, 2};

  int rock_xi[] = {4, 4, 4};
  int rock_yi[] = {4, 5, 6};

  int barrier_xi[] = {5, 5, 5};
  int barrier_yi[] = {0, 1, 2};

  int teleport_xi[2] = {0, 1};
  int teleport_yi[2] = {7, 2};

  int lava_xi[] = {6, 6, 6};
  int lava_yi[] = {0, 1, 2};

  for (int i=0; i< (sizeof (water_xi)/sizeof (int)); i++)
    board_.set (water_xi[i], water_yi[i], WATER);

  for (int i=0; i< (sizeof (rock_xi)/sizeof (int)); i++)
    board_.set (rock_xi[i], rock_yi[i], ROCK);

  for (int i=0; i< (sizeof (barrier_xi)/sizeof (int)); i++)
    board_.set (barrier_xi[i], barrier_yi[i], BARRIER);

  for (int i=0; i< (sizeof (teleport_xi)/sizeof (int)); i++)
    board_.set (teleport_xi[i], teleport_yi[i], TELEPORT);

  for (int i=0; i< (sizeof (lava_xi)/sizeof (int)); i++)
    board_.set (lava_xi[i], lava_yi[i], LAVA);


}

void knight_t::set_board_cost_32x32(board_t &board_)
{
  board_.reset(0); // set all cells to 0

  int water_xi[] = {2, 2, 2};
  int water_yi[] = {0, 1, 2};

  int rock_xi[] = {4, 4, 4};
  int rock_yi[] = {4, 5, 6};

  int barrier_xi[] = {5, 5, 5};
  int barrier_yi[] = {0, 1, 2};

  int teleport_xi[2] = {0, 1};
  int teleport_yi[2] = {7, 2};

  int lava_xi[] = {6, 6, 6};
  int lava_yi[] = {0, 1, 2};

  for (int i=0; i< (sizeof (water_xi)/sizeof (int)); i++)
    board_.set (water_xi[i], water_yi[i], WATER);

  for (int i=0; i< (sizeof (rock_xi)/sizeof (int)); i++)
    board_.set (rock_xi[i], rock_yi[i], ROCK);

  for (int i=0; i< (sizeof (barrier_xi)/sizeof (int)); i++)
    board_.set (barrier_xi[i], barrier_yi[i], BARRIER);

  for (int i=0; i< (sizeof (teleport_xi)/sizeof (int)); i++)
    board_.set (teleport_xi[i], teleport_yi[i], TELEPORT);

  for (int i=0; i< (sizeof (lava_xi)/sizeof (int)); i++)
    board_.set (lava_xi[i], lava_yi[i], LAVA);
}

/***
    Displays the path as numbers on the board
*/
void knight_t::display_path_on_board(path_t const &path_, int dim_size_)
{
  board_t brd (dim_size_);
  brd.reset(0);
  for (int i=0; i< path_.size(); i++)
    {
      brd.set(path_[i].xi, path_[i].yi, i+1);
    }
  brd.display_board();
}

void knight_t::scan_board_diagram(string filePath_, 
				  board_t &brd_,
				  int DIM_SIZE_)
{
  string line;
  ifstream myfile (filePath_);

  if (myfile.is_open())
    {
      int row_i = 0;
      while ( getline (myfile,line) &&
	      (row_i < DIM_SIZE_)) //to ignore more lines
	{
	  int col_i =0;
	  for (int i=0; i< line.size(); i=i+2)
	    {
	      //printf("%c|",line[i]);
	      switch (line[i])
		{
		case 'W':
		  //printf("B (%d,%d)\n",row_i, col_i);
		  brd_.set (col_i, row_i, WATER);
		  break;
		case 'R':
		  //printf("B (%d,%d)\n",row_i, col_i);
		  brd_.set (col_i, row_i, ROCK);
		  break;
		case 'B':
		  //printf("B (%d,%d)\n",row_i, col_i);
		  brd_.set (col_i, row_i, BARRIER);
		  break;
		case 'T':
		  //printf("B (%d,%d)\n",row_i, col_i);
		  brd_.set (col_i, row_i, TELEPORT);
		  break;
		case 'L':
		  //printf("B (%d,%d)\n",row_i, col_i);
		  brd_.set (col_i, row_i, LAVA);
		  break;
		}

	      col_i++;
	      // skip extra characters in line
	      if (col_i >= DIM_SIZE_)
		break;
	    }
	  row_i++;
	}
      myfile.close();
    }

  else cout << "Unable to open file";


}

/***
 */
bool knight_t::scan_path_string (string indata_, 
				 int &dim_size_,
				 path_t &path_)
{

  char *str;
  const char delimiters[] = ", ";

  str = strdup (indata_.c_str());
  //  strcpy (str, indata.c_str ());
  char *ch_key = strtok (str, delimiters);

  sscanf (ch_key, "%d", &dim_size_);
  ch_key = strtok (NULL, delimiters);

  while (ch_key != NULL)
    {
      int xi;
      int yi;

      sscanf(ch_key, "%d",&xi);
      ch_key = strtok (NULL, delimiters);

      if (ch_key == NULL)
	return false;
      sscanf(ch_key, "%d",&yi);
      ch_key = strtok (NULL, delimiters);
      
      cell_ind_t nd;
      nd.xi = xi;
      nd.yi = yi;
      path_.push_back(nd);
    }
  return true;
}

bool knight_t::scan_dim_src_dest (string indata_, 
				  int &dim_size_,
				  cell_ind_t &src_,
				  cell_ind_t &dest_)
{
  char *str;
  const char delimiters[] = ", ";

  str = strdup (indata_.c_str());
  //  strcpy (str, indata.c_str ());
  char *ch_key = strtok (str, delimiters);

  sscanf (ch_key, "%d", &dim_size_);
  ch_key = strtok (NULL, delimiters);

  if (ch_key == NULL)
    return false;
  sscanf (ch_key, "%d", &(src_.xi));
  ch_key = strtok (NULL, delimiters);

  if (ch_key == NULL)
    return false;
  sscanf (ch_key, "%d", &(src_.yi));
  ch_key = strtok (NULL, delimiters);

  if (ch_key == NULL)
    return false;
  sscanf (ch_key, "%d", &(dest_.xi));
  ch_key = strtok (NULL, delimiters);

  if (ch_key == NULL)
    return false;
  sscanf (ch_key, "%d", &(dest_.yi));
  ch_key = strtok (NULL, delimiters);

  return true;
}
