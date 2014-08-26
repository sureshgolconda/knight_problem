
#include "board.H"

using namespace knight_t;

/***
    Display board with descriptive labels
*/
void board_t::display_board()
{
  for (int y=0; y<DIM_SIZE; y++)
    {
      for (int x=0; x< DIM_SIZE; x++)
	switch(m_cells[x][y].value)
	  {
	  case WATER:
	    printf("| W");
	    break;  
	  case ROCK:
	    printf("| R");
	    break;  
	  case BARRIER:
	    printf("| B");
	    break;  
	  case TELEPORT:
	    printf("| T");
	    break;  
	  case LAVA:
	    printf("| L");
	    break;  
 	  case BLOCKED:
	    printf("|  ");
	    break;  

 	  case KNIGHT_C:
	    printf("| K");
	    break;  

	  case 0: // leave blank for 0 value, visual effect
	    printf("|  ");
	    break;

	  default:
	    printf("|%2d", m_cells[x][y].value);
	    break;  
	  }

      printf("|\n");
    }
}



void board_t::display_move(cell_ind_t const &move_)
{
  // store the original value of the cell
  short org_value = m_cells[move_.xi][move_.yi].value;
  // mark present cell as knight
  m_cells[move_.xi][move_.yi].value = KNIGHT_C;
  // display board
  //	  printf("\nPosition (%d, %d)\n",move_.xi, move_.yi);
  display_board();
  //restore original value
  m_cells[move_.xi][move_.yi].value = org_value;
}



void board_t::display_path(path_t const &moves_)
{
  for (int i=0; i< moves_.size(); i++)
    {
      printf("\nMove-%d (%d, %d)\n", i, moves_[i].xi, moves_[i].yi);
      display_move (moves_[i]);
    }
}



void board_t::set_teleport_cells(int teleport_xi_[], int teleport_yi_[])
{
  // empty the list first
  m_teleport_xi.clear();
  m_teleport_yi.clear();

  // enter the  new entries
  for (int i=0; i < (sizeof (teleport_xi_)/sizeof(teleport_xi_[0])); i++)
    {
      m_teleport_xi.push_back (teleport_xi_[i]);
      m_teleport_yi.push_back (teleport_yi_[i]);
    }
}


void board_t::reset(int value_)
{
  for (int x=0; x< DIM_SIZE; x++)
    for (int y=0;y< DIM_SIZE; y++)
      {
	m_cells[x][y].value = value_; // default value      
	m_cells[x][y].parent_xi = -1; // default value      
	m_cells[x][y].parent_yi = -1; // default value      
      }
}


bool board_t::check_valid_path(path_t const &path_, bool display_)
{
  if (path_.empty())
    return true; // return true if list is empty

  // check if the cell falls within board
  for (int i=0; i< path_.size(); i++)
    {
      if ((path_[i].xi <0) || (path_[i].yi <0)  ||
	  (path_[i].xi >= DIM_SIZE) || 
	  (path_[i].yi >= DIM_SIZE))
	{
	  if (display_)
	    printf("Out of board path (%d, %d)\n", 
		   path_[i].xi, path_[i].yi);
	  return false;
	}
    }

  // initial move
  if (display_)
    {
      printf("Move 0: (%d, %d)\n", path_[0].xi, path_[0].yi);
      display_move(path_[0]);
    }

  // check if the moves are valid
  for (int i=1; i< path_.size(); i++)
    {
      if (display_)
	{
	  printf("\nMove %d: (%d, %d)\n", i, path_[i].xi, path_[i].yi);
	  display_move (path_[i]);
	}
	  
      if ((!knight_neighbor (path_[i-1], path_[i])) &&
	  (!teleport_points(path_[i-1], path_[i])))
	{
	  if (display_)
	    printf("Bad move %d from (%d, %d) to (%d, %d)\n", i,
		   path_[i-1].xi, path_[i-1].yi,
		   path_[i].xi, path_[i].yi);

	  return false;
	}
    }


      

  return true;
}
