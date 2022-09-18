#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 3
#define N n*n
#define UNASSIGNED 0

extern int iteration;
extern int parity[][2], asterisk[][2], girandola[][2];
extern int parity_size, asterisk_size, girandola_size;

// finds first unassigned number in each grid
inline int find_unassigned(int grid[N][N], int* row, int* col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == UNASSIGNED) {
				return 1;
			}
		}
	}
	return 0;
}

// standard conditions for normal sudoku
inline int is_exist_row(int grid[N][N], int row, int num) {
	for (int col = 0; col < N; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}
inline int is_exist_col(int grid[N][N], int col, int num) {
	for (int row = 0; row < N; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}
inline int is_exist_box(int grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			}
		}
	}
	return 0;
}

// custom conditions for each variant of sudoku. Returns 1 if condition is broken, returns 0 if not
inline int is_exist_X(int grid[N][N], int row, int col, int num) {
	if (row == (N - 1) - col) {
		for (row = 0; row < N; row++) {
			if (grid[row][(N - 1) - row] == num)
				return 1;
		}
	} 
	else if (row == col) {
		for (row = 0; row < N; row++) {
			if (grid[row][row] == num)
				return 1;
		}
	}
	return 0;
}
inline int is_exist_dot(int grid[N][N], int row, int col, int num) {
	if (row % 3 == 1 && col % 3 == 1) {
		for (row = 1; row < N; row += 3) {
			for (col = 1; col < N; col += 3) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	return 0;
}
inline int is_exist_hyper(int grid[N][N], int row, int col, int num) {
	// top boxes
	if (row > 0 && row <= 3) {
		if (col > 0 && col <= 3) {
			for (row = 1; row <= 3; row++) {
				for (col = 1; col <= 3; col++) {
					if (grid[row][col] == num) 
						return 1;
				}
			}
		}
		else if (col > 4 && col <= 7) {
			for (row = 1; row <= 3; row++) {
				for (col = 5; col <= 7; col++) {
					if (grid[row][col] == num)
						return 1;
				}
			}
		}
	}
	// bottom boxes
	else if (row > 4 && row <= 7) {
		if (col > 0 && col <= 3) {
			for (row = 5; row <= 7; row++) {
				for (col = 1; col <= 3; col++) {
					if (grid[row][col] == num)
						return 1;
				}
			} 
		}
		else if (col > 4 && col <= 7) {
			for (row = 5; row <= 7; row++) {
				for (col = 5; col <= 7; col++) {
					if (grid[row][col] == num)
						return 1;
				}
			} 
		}
	}
	return 0;
}
inline int is_exist_parity(int grid[N][N], int row, int col, int num, char type[]) {
	int i;
	for (i = 0; i < parity_size; i++) {
		if (parity[i][0] == row && parity[i][1] == col) {
			if (strcmp(_strlwr(type), "odd") == 0) {
				if (num % 2 == 1)
					return 0;
			}
			else if (strcmp(_strlwr(type), "even") == 0) {
				if (num % 2 == 0)
					return 0;
			}
			return 1;
		}
	}
	return 0;
}
inline int is_exist_argyle(int grid[N][N], int row, int col, int num) {
	// 2nd \ diagonal
	if (row == col + 1) {
		for (row = 1; row < N; row++) {
			if (grid[row][row - 1] == num)
				return 1;
		}
	}
	// 3rd \ diagonal
	else if (row == col - 1) {
		for (row = 0; row < N; row++) {
			if (grid[row][row + 1] == num)
				return 1;
		}
	}
	// 1st \ diagonal
	else if (row == col + 4) {
		for (row = 4; row < N; row++) {
			if (grid[row][row - 4] == num)
				return 1;
		}
	}
	// 4th \ diagonal
	else if (row == col - 4) {
		for (row = 0; row < N; row++) {
			if (grid[row][row + 4] == num)
				return 1;
		}
	}
	// 2nd / diagonal
	else if (row == (N - 1) - col - 1) {
		for (row = 0; row < N; row++) {
			if (grid[row][(N - 1) - row - 1] == num)
				return 1;
		}
	}
	// 3rd / diagonal
	else if (row == (N - 1) - col + 1) {
		for (row = 1; row < N; row++) {
			if (grid[row][(N - 1) - row + 1] == num)
				return 1;
		}
	}
	// 1st / diagonal
	else if (row == (N - 1) - col - 4) {
		for (row = 0; row < N; row++) {
			if (grid[row][(N - 1) - row - 4] == num)
				return 1;
		}
	}
	// 4th / diagonal
	else if (row == (N - 1) - col + 4) {
		for (row = 4; row < N; row++) {
			if (grid[row][(N - 1) - row + 4] == num)
				return 1;
		}
	}
	return 0;
}
inline int is_exist_asterisk(int grid[N][N], int row, int col, int num) {
	int i, j;
	for (i = 0; i < asterisk_size; i++) {
		if (row == asterisk[i][0] && col == asterisk[i][1]) {
			for (j = 0; j < asterisk_size; j++) {
				if (grid[asterisk[j][0]][asterisk[j][1]] == num)
					return 1;
			}
		}
	}
	return 0;
}
inline int is_exist_girandola(int grid[N][N], int row, int col, int num) {
	int i, j;
	for (i = 0; i < girandola_size; i++) {
		if (row == girandola[i][0] && col == girandola[i][1]) {
			for (j = 0; j < girandola_size; j++) {
				if (grid[girandola[j][0]][girandola[j][1]] == num)
					return 1;
			}
		}
	}
	return 0;
}
inline int is_exist_offset(int grid[N][N], int row, int col, int num) {
	// top left digit
	if (row % n == 0 && col % n == 0) {
		for (row = 0; row < N; row += n) {
			for (col = 0; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// top middle digit
	if (row % n == 0 && col % n == 1) {
		for (row = 0; row < N; row += n) {
			for (col = 1; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// top right digit
	if (row % n == 0 && col % n == 2) {
		for (row = 0; row < N; row += n) {
			for (col = 2; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// center left digit
	if (row % n == 1 && col % n == 0) {
		for (row = 1; row < N; row += n) {
			for (col = 0; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// center middle digit
	if (row % n == 1 && col % n == 1) {
		for (row = 1; row < N; row += n) {
			for (col = 1; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// center right digit
	if (row % n == 1 && col % n == 2) {
		for (row = 1; row < N; row += n) {
			for (col = 2; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// bottom left digit
	if (row % n == 2 && col % n == 0) {
		for (row = 2; row < N; row += n) {
			for (col = 0; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// bottom middle digit
	if (row % n == 2 && col % n == 1) {
		for (row = 2; row < N; row += n) {
			for (col = 1; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	// bottom right digit
	if (row % n == 2 && col % n == 2) {
		for (row = 2; row < N; row += n) {
			for (col = 2; col < N; col += n) {
				if (grid[row][col] == num)
					return 1;
			}
		}
	}
	return 0;
}
inline int is_exist_nc(int grid[N][N], int row, int col, int num) {
	if (row == 0) {
		if (col == 0) {
			if (abs(num - grid[row][col + 1]) == 1 || 
				abs(num - grid[row + 1][col]) == 1)
				return 1;
			return 0;
		}
		else if (col == N - 1) {
			if (abs(num - grid[row][col - 1]) == 1 ||
				abs(num - grid[row + 1][col]) == 1)
				return 1;
			return 0;
		}
		else
			if (abs(num - grid[row][col - 1]) == 1 ||
				abs(num - grid[row][col + 1]) == 1 ||
				abs(num - grid[row + 1][col]) == 1)
				return 1;
		return 0;
	}
	return 0;
}

// functions that check necessary conditions for each digit on a sudoku variant
inline int is_safe_num_norm(int grid[N][N], int row, int col, int num) {
	if (!is_exist_row(grid, row, num) &&
		!is_exist_col(grid, col, num) &&
		!is_exist_box(grid, row - (row % n), col - (col % n), num))
		return 1;
	return 0;
}
inline int is_safe_num(int grid[N][N], int row, int col, int num, char type[]) {
	if (is_safe_num_norm(grid, row, col, num)) {
		if (strcmp(_strlwr(type), "x") == 0) {
			if (!is_exist_X(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "dot") == 0) {
			if (!is_exist_dot(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "hyper") == 0) {
			if (!is_exist_hyper(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "even") == 0 || strcmp(_strlwr(type), "odd") == 0) {
			if (!is_exist_parity(grid, row, col, num, type))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "argyle") == 0) {
			if (!is_exist_argyle(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "asterisk") == 0) {
			if (!is_exist_asterisk(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "girandola") == 0) {
			if (!is_exist_girandola(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "offset") == 0) {
			if (!is_exist_offset(grid, row, col, num))
				return 1;
			return 0;
		}
		else if (strcmp(_strlwr(type), "non-consecutive") == 0 || strcmp(_strlwr(type), "nc") == 0) {
			if (!is_exist_nc(grid, row, col, num))
				return 1;
			return 0;
		}
		return 1;		
	}
	return 0;
}

/* 
checks if each nonzero digit is safe in the current grid.
If each nonzero digit is safe, then the function produces 1, else produces 0.
*/
//inline int digit_safe(int grid[N][N], int row, int col, char type[]) {
//	int (*check_grid) [N] = { grid };
//	*( *(check_grid + row) + col) = 0;
//
//	// dereferences pointer to jth element of its ith N-D array
//	int num = grid[row][col];
//
//	if (num != 0)
//		return is_safe_num(check_grid, row, col, num, type);
//	return 1;
//}

// inserts digit into each spot and backtracks if unable
inline int solve(int grid[N][N], char type[]) {

	int row = 0;
	int col = 0;

	if (!find_unassigned(grid, &row, &col)) {
		return 1;
	}

	for (int num = 1; num <= N; num++) {
		if (is_safe_num(grid, row, col, num, type)) {
			grid[row][col] = num;

			if (solve(grid, type)) {
				return 1;
			}
			grid[row][col] = UNASSIGNED;
		}
	}
	iteration++;
	return 0;
}