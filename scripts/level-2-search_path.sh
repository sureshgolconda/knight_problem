#!/bin/bash
# Authors: Suresh Golconda

# presently this is same as leve-3.
# 1st argument 8- size of the board (8x8), followed by 
# start point(x,y), end point (x,y)

time  echo "8, 0,0, 7, 7" | ../bin/knight_path -s
