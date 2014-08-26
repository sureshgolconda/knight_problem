#!/bin/bash
# Authors: Suresh Golconda

time cat ../data/sample_path_good.txt | ../bin/knight_path -v

# or
# Stream, board size followed by pair of points along the path

# echo "8,    0,0,  1,2,  2,4,    3,2"| ../bin/knight_path -v