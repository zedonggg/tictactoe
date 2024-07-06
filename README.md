## Tic-Tac-Toe in C++ ##
This README will detail my try at coding a tic-tac-toe game in C++. 

## Usage ##
Build using min C++11 and run the file. You will be prompted to enter if you are playing first or not. If you are playing first, type `1` and hit enter. If you are not playing first, type `0` and hit enter (computer will play first). 

When it is your (the player's) turn, you will be prompted to `Enter the row and column separated by a space`. Enter a zero-indexed row and column value, starting from 0 and ending at 2. For example, to play in the middle grid (the second column of the second row), type `1 1` and press enter. Error checking is a bit spotty so try not to input invalid numbers or grids that are already taken!

The game will automatically check if the computer or the player has won or if it is a draw and print the corresponding statement.

## R1 ##
I use a class to encapsulate the game board, with the game driver code under main(). The computer uses a rudimentary minimax algorithm to compute the optimal move to play. Since we only have to search a maximum of 19,683 different combinations (board states), we do not bother with depth limitations for now as the absolute running time of the minimax function is trivial. The reference for the minimax algo can be found in the source code under `main.cpp`.

The running time of the minimax algorithm was logged using chrono and the results are shown below. One rudimentary optimization that is implemented is checking for grids that are already taken, so the minimax search will only be performed on empty grids where a move is possible. As such, the running time exponentially falls with subsequent calls to the minimax function as the game board becomes more populated.

**Running time in microseconds when computer goes first**
Moves input into console : `1 1`, `0 2`, `1 0`
| Turns executed | Reading 1 | Reading 2 | Reading 3 |
| --- | --- | --- | --- |
| 0 | 70262 | 67373 | 67267 |
| 2 | 1193 | 1184 | 1135 |
| 4 | 49 | 49 | 34 |
| 6 | 5 | 5 | 6 |

**Running time in microseconds when computer goes last**
Moves input into console : `1 1`, `0 2`, `1 0`
| Turns executed | Reading 1 | Reading 2 | Reading 3 |
| --- | --- | --- | --- |
| 0 | 70262 | 67373 | 67267 |
| 2 | 1193 | 1184 | 1135 |
| 4 | 49 | 49 | 34 |
| 6 | 5 | 5 | 6 |

