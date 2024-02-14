
			Readme File for knight problem

Overview:
---------
Present system tries to implement 4 problems
1) Checking if a given path is a valid knight path
2) Find a path from given source to given destination cell on a (8x8) chess board
3) Shortest path from given source to given destination (8x8) chess board
4) Shortest path on a 32x32 cheess board with more rules for {water, rock, etc}.

Notes:
------
- Board configuration can be provided as a text (diagram) file. Check data/board_diagram.txt.
- Included gprof profiling of the program in 'analysis' sub folder
- Script folder contain ready to run (no arguments) for each of the questions.
- Including code documentation as HTML and PDF, in 'docs' folder
- Scripts also print the time profile of running the program. Simple 'time' linux command


Organization:
-------------
src: Contains c++ code 
data: Contains sample input files and board configuration.
script: Contains scripts for running each of the 4 problems with required program parameters.
analysis: Contains sample gprof profiling output
docs: Contains code document generated using Doxygen in html and .pdf format 

Instructions:
-------------
Compile:
$cd src
$ make

Run:
$cd scripts
$./<script_name>
eg: $ ./level-1_good_path.sh


Terminology:
------------
Board: Is the chess board reprsentation. Present system only considers square board.

Path: Sequence of knight steps (cell position).

Move: Same as step (cell position).

DIM_SIZE: Dimesion of the board, DIM_SIZE=8, implies 8x8 board.

Base board: Is the board maintain to maintain cell configuration {Water, Rock, etc..}. For ease of inputing this configuration, the program accepts a text file with board represented as a diagram. Check "data/board_diagram.txt" sample file.


Algorithm:
----------
- Present implemented search algorithms include 'Best-First-Search' (http://en.wikipedia.org/wiki/Best-first_search).
 For level-2, and level-3, a cost of 1 is added for each of the step of the knight.
 Apart from above cost, additional cost is assigned based on the if the related cells are marked as {Water, Rock, Barrier, Lava}.
 

Classes:
--------
- board_t: Class for board state
- search_path_t: Class for searching


Todo:
-----
Change emacs's tab size
update valid path check to check for teleport entries (done)


======================================================

Board Configuration:
------------
- Board state is read from a easy to enter text file. Can copy paste board diagram from problem description pdf.
- The system will cleanly ignore extra rows/columns. It expects {., W, R, B, T, L} values seperated with space (" ").
- To make sure the system interpreted the board configuration correctly, it displays the 'Base Board' at the terminal.
- Present assumption is that equal number of rows and columns exist (square board).


Create Doxygen documentat of the code:
--------------------------------------
- From 'src' folder, type following. May require to install doxygen.
  $ doxygen
- Will create documentation in ../docs folder.
- To create pdf of the document, enter docs/latex folder and type 'make'. Will require to have following installed: latex, texlive-fonts-recommended, ghostscript.


Troubleshooting:
----------------
- After checkingout of the code, if not able to run the scripts, check to make sure scripts have got the executable permission "x".
