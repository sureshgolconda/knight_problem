#!/bin/bash
# Authors: Suresh Golconda

# 1st number echo-ing is size of the board (32x32), followed by start
# point(x,y), end point (x,y)

#echo "dimension, start_x,start_y,    end_x,end_y
time echo "32, 0,0, 31, 31" | ../bin/knight_path -s -b ../data/board_diagram.txt

