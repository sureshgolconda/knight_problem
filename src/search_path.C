#include "search_path.H"

#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace knight_t;

int search_path_t::new_cost (const node_t &nd, int nxi, int nyi)
{
  int cost =0;
  // cost from dest cell
  int dest_cell_type = m_base_board->value(nxi,nyi);
  if (dest_cell_type == WATER)
    cost += WATER_COST;
  else
    if (dest_cell_type == LAVA)
      cost += LAVA_COST;
    else
      if ((dest_cell_type == ROCK) ||
	  (dest_cell_type == BARRIER))
	return INT_MAX;

  // cost along the path
  // two possible paths from source to dest
  int delx = nxi - nd.xi;
  int dely = nyi - nd.yi;
  assert (((abs(delx) == 2) && (abs(dely) == 1)) ||
	  ((abs(delx) == 1) && (abs(dely) == 2)));
  intermediate_steps_t const* path1 = move_intersteps (delx, dely);
  intermediate_steps_t const* path2 = path1 + 1;

  if (move_blocked (nd, path1) &&
      move_blocked (nd, path2)) // if both possible
    return INT_MAX; // no path
  

  if (cost ==0) // if normal cell
    cost = 1;
  return nd.value + cost;
}

bool search_path_t::move_blocked (const node_t &nd, intermediate_steps_t const* path)
{
  int sxi; //step-x index
  int syi; //step-y index

  // 1st step in the move
  sxi = nd.xi + path->dx[0];
  syi = nd.yi + path->dy[0];
  if (m_base_board->value(sxi, syi) == BARRIER)
    return true; // is a barrier


  // 2nd step in the move
  sxi = nd.xi + path->dx[1];
  syi = nd.yi + path->dy[1];
  if (m_base_board->value(sxi, syi) == BARRIER)
    return true; // is a barrier


  // not blocked by barrier
  return false;
}

void search_path_t::set_teleport_nav(node_t const &nd, board_t &search_bd,
				     priority_queue<node_t> &pq)
{
  std::vector <int> const teleport_xi = m_base_board->get_teleport_x();
  std::vector <int> const teleport_yi = m_base_board->get_teleport_y();

  for (int i=0; i< teleport_xi.size(); i++)
    {
      if (m_debug)
	printf("tele port cells (%d, %d)\n", 
	       teleport_xi[i], teleport_yi[i]);
      if ((nd.xi != teleport_xi[i]) && (nd.yi != teleport_yi[i]))
	{ // not the present source cells
	  //check the cost of new tele node, should be greater or equal
	  int tele_value = search_bd.value (teleport_xi[i],
					    teleport_yi[i]);

	  assert (tele_value >= nd.value);
	  if (tele_value > nd.value) // to avoid looping between tele
	    {
	      node_t tele_nd (teleport_xi[i], teleport_yi[i],
			      nd.xi, nd.yi); // create new node
	      tele_nd.value = nd.value; // set new value

	      //update search grid
	      search_bd.set(tele_nd.xi, tele_nd.yi, tele_nd.value,
			    nd.xi, nd.yi);
	      if (m_debug)
		printf("\t TELE: (%d, %d)=%d\n", tele_nd.xi, tele_nd.yi, 
		       tele_nd.value);
	      pq.push(tele_nd); // push new node to queue
	    }
	}
    }
}

search_path_t::intermediate_steps_t const* search_path_t::move_intersteps(int delx, int dely)
    { // note: y axis increases going down.
      //top, top, right
      static const intermediate_steps_t paths_TTR[2] {intermediate_steps_t(0,-1,   0,-2), // 1 O'clock
	  intermediate_steps_t(1,0,    1,-1)};
      //top, right, right
      static const intermediate_steps_t paths_TRR[2] {intermediate_steps_t(0,-1,   1,-1), // 2 O'clock
	  intermediate_steps_t(1,0,    2,0)};


      //down, right, right
      static const intermediate_steps_t paths_DRR[2] {intermediate_steps_t(1,0,   2,0), // 4 O'clock
	  intermediate_steps_t(0,1,   1,1)};
      //down, down, right
      static const intermediate_steps_t paths_DDR[2] {intermediate_steps_t(1,0,   1,1), // 5 O'clock
	  intermediate_steps_t(0,1,   0,2)};


      //down, down, left
      static const intermediate_steps_t paths_DDL[2] {intermediate_steps_t(-1,0,   -1,1), // 7 O'clock
	  intermediate_steps_t(0,1,    0,2)};
      // downl, left, left
      static const intermediate_steps_t paths_DLL[2] {intermediate_steps_t(-1,0,   -2,0), // 8 O'clock
	  intermediate_steps_t(0,1,    -1,1)};


      // top, left, left
      static const intermediate_steps_t paths_TLL[2] {intermediate_steps_t(0,-1,   -1,-1), // 10 O'clock
	  intermediate_steps_t(-1,0,   -2,0)};
      // top, top, left
      static const intermediate_steps_t paths_TTL[2] {intermediate_steps_t(0,-1,   0,-2), // 11 O'clock
	  intermediate_steps_t(-1,0,   -1,-1)};

      if ((delx == 1) && (dely == -2)) // 1 O'clock
	return  &paths_TTR[0];
      else
	if ((delx == 2) && (dely == -1)) // 2 O'clock
	  return &paths_TRR[0];
	else
	  if ((delx == 2) && (dely == 1)) // 4 O'clock
	    return &paths_DRR[0];

	  else
	    if ((delx == 1) && (dely == 2)) // 5 O'clock
	      return &paths_DDR[0];

	    else
	      if ((delx == -1) && (dely == 2)) // 7 O'clock
		return &paths_DDL[0];

	      else
		if ((delx == -2) && (dely == 1)) // 8 O'clock
		  return &paths_DLL[0];

		else
		  if ((delx == -2) && (dely == -1)) // 10 O'clock
		    return &paths_TLL[0];

		  else
		    if ((delx == -1) && (dely == -2)) // 11 O'clock
		      return &paths_TTL[0];
      return &paths_TTR[0];
    }









void search_path_t::trace_path(node_t const &dest, node_t const &src,
			       board_t &search_bd, path_t &path_)
{
  // printf("Tracing the path (%d, %d) to src (%d %d)\n", dest.xi, dest.yi,
  // 	 src.xi, src.yi);

  path_t temp_path;
  cell_ind_t cell_ind;
  cell_ind.xi = dest.xi;
  cell_ind.yi = dest.yi;
  temp_path.push_back (cell_ind);

  cell_t cell = search_bd.get(cell_ind.xi, cell_ind.yi);

  while ((cell.parent_xi !=-1) &&(cell.parent_yi !=-1))

    {
      //      printf("parent %d %d\n", cell.parent_xi, cell.parent_yi);
      cell_ind.xi = cell.parent_xi;
      cell_ind.yi = cell.parent_yi;
      temp_path.push_back (cell_ind);

      if ((cell.parent_xi == src.xi) && (cell.parent_yi == src.yi))
      {
	//	printf("Found complete path\n");
	break;
      }

      cell = search_bd.get (cell.parent_xi, cell.parent_yi);
      //printf("\t new cell (%d %d)\n", cell.parent_xi, cell.parent_yi);
    }

  // reverse the path
  path_.clear();
  for (int i=temp_path.size()-1; i>=0; i--)
    {
      path_.push_back (temp_path[i]);
    }

  printf("\nPath:");
  for (int i=0; i< path_.size(); i++)
    printf("(%d, %d)  ", path_[i].xi, path_[i].yi);
  printf("\n");
}
bool search_path_t::get_path (int sxi_, int syi_, int exi_, int eyi_, path_t &path_)
    {
      //printf("get path(): %d %d, %d %d, sz=%d\n", sxi_, syi_, exi_, eyi_, DIM_SIZE);
      // ---- initialization of env ---
      // relative steps to 8 neighboring moves
      static int nx_delta[8] = {2, 1, -1, -2, -2, -1,  1,  2};
      static int ny_delta[8] = {1, 2,  2,  1, -1, -2, -2, -1};
      //set_board_cost();


      //m_board.reset (SHRT_MAX);
      board_t search_bd(DIM_SIZE);
      search_bd.reset(INT_MAX);

      node_t src (sxi_, syi_, -1, -1);
      node_t dest (exi_, eyi_, -1, -1);
      src.value = 0;
      dest.value = 0;

      search_bd.set(src.xi, src.yi, src.value);

      std::priority_queue<node_t> pq;
      pq.push(src);

      unsigned count =0;
      int cost_depth =0;  // max cost node
      int solution_depth = 0; // solution depth
      bool path_found = false;

      while (!pq.empty())
	{
	  count++;
	  node_t nd = pq.top();
	  if (m_debug)
	    printf("nd=(%d %d)=%d size=%lu\n", nd.xi, nd.yi, nd.value, pq.size());
	  pq.pop();
	  solution_depth = max (solution_depth, nd.value);

	  //todo: check if the node's value is same as in search grid. else discard

	  if (nd == dest)
	    {
	      printf("Goal reached (%d %d) at cost=%d, iterations=%d, max cost cell=%d\n",
		     nd.xi, nd.yi, nd.value, count, cost_depth);
	      trace_path(nd, src, search_bd, path_);
	      path_found = true;
	      break;
	    }
	  // check if it is a teleport cell
	  if (m_base_board->value (nd.xi, nd.yi) == TELEPORT)
	    { // create a another node with same cost
	      if (m_debug)
		printf("Found teleport cell (%d,%d)\n", nd.xi, nd.yi);
	      set_teleport_nav(nd, search_bd, pq);
	    }

	  for (int i=0; i< NUM_NEIGHBORS; i++)
	    {
	      int nxi = nd.xi + nx_delta [i];
	      int nyi = nd.yi + ny_delta [i];
	      if ((nxi <0) || (nxi >= DIM_SIZE) ||
		  (nyi <0) || (nyi >= DIM_SIZE))
		continue; //out of board
	      int val = search_bd.value(nxi, nyi);
	      //int new_val= nd.value + 1; // set custom cost
	      int new_val= new_cost (nd, nxi, nyi);//nd.value + 1; // set custom cost


		if ((new_val != INT_MAX) &&//is not blocked cell
		    (new_val <val)) //push to queue
		{
		  node_t ng_nd (nxi, nyi, nd.xi, nd.yi); // create new node
		  ng_nd.value = new_val; // set new value
		  cost_depth = max (cost_depth, new_val);

		  search_bd.set(nxi, nyi, new_val, nd.xi, nd.yi); //update search grid
		  if (m_debug)
		    printf("\t (%d, %d)=%d\n", nxi, nyi, new_val);
		  pq.push(ng_nd); // push new node to queue
		}
	      // else
	      // 	printf("NOT adding: (%d %d, %d with %d)\n",
	      // 	       nxi, nyi, val, new_val);

	    }
	}
      printf("Search board with cost values\n");
      search_bd.display_board();
      return path_found;
    }
