# Multi-Sudoku-console
WORK IN PROGRESS

A Windows console C program run on Visual Studio that can solve Sudoku puzzles in multiple versions. The program will take an inputted (or empty) 9x9 grid and output the completed grid, along with the number of backtracking iterations to complete the Sudoku grid. The program can solve Sudoku puzzles in the following variants. 

| Variant | Description |
| - | - |
| X | 2 diagonals must have numbers 1-9. |
| Dot | Centre numbers in all 3x3 boxes are unique to one another. |
| Hyper | 4 center 3x3 boxes have numbers 1-9. |
| Parity | Numbers in highlighted boxes are either odd or even. |
| Argyle | Select diagonals must have unique numbers. |
| Offset | Each position within each 3x3 box is a new region with numbers 1-9. |
| Non-consecutive | Vertically and horizonatally adjacent cells don't have consecutive numbers. | 
| Asterisk & Girandola | Select cells are a new region with numbers 1-9. |

You must edit the "chosen_type" variable in the program to change the sudoku variant.

