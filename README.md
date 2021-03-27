# About
This C program solves the N-Queen problem on a triangular M-sized board. The goal is to place N number of Queens on a triangular chess board of side length M such that the Queens do not attack each other. 

![Problem Image](http://poj.org/images/3091_1.png) 

Figure 1 shows an example of which tiles a Queen can attack from a certain position.
Figure 2 shows one possible solution of M = 6, N = 4 problem.

The program uses a bruteforce recursive algorithm with backtracking to try all possible configurations until a solution is or is not found. A text file "protokolas.txt" is output, in which all steps are written along with the resulting solution.

Maximum values of M and N are implemented so that the program does not run for too long, however, it can be changed if desired.
* Maximum of M is 12.
* Maximum of N is 8.

Currently the output is in Lithuanian, however, work is being done to translate it into English.

# Usage
* Open "N-queen-triangle.c" in a text editor and change define values of M and N to desired ones but not higher than 12 and 8, respectively.
* Open terminal in the downloaded folder and enter "gcc N-queen-triangle.c -o main" after which an executable is created.
* Launch program by entering ".\main".
* Open "protokolas.txt" to see the results.
