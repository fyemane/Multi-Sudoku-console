//https://gist.github.com/bopbi/c9f94b1b981b84bcb02b
#define _CRT_SECURE_NO_WARNINGS
#include "mycolors.c"
#include "sudoku.c"

#define c 22

int chars[] = {
	'1', '2', '3', '4',
	'5', '6', '7', '8',
	'9', 'A', 'B', 'C',
	'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P' };
char KCOL[c];
iteration = 1;
 
char variants[10][20] = { "x", "dot", "hyper", "odd", 
						"even", "argyle", "asterisk", "girandola",
						"offset", "non-consecutive" };
int variants_size = sizeof variants / sizeof * variants;

parity[][2] = { {1, 2}, {2, 1}, {2, 2}, {1, 6}, {2, 6}, {2, 7},
	{6, 1}, {6, 2}, {7, 2}, {6, 6}, {6, 7}, {7, 6} };
parity_size = sizeof parity / sizeof * parity;
asterisk[][2] = { {2, 2}, {1, 4}, {2, 6},
	{4, 1}, {4, 4}, {4, 7},
	{6, 2}, {7, 4}, {6, 6} };
asterisk_size = sizeof asterisk / sizeof * asterisk;
girandola[][2] = { {0, 0}, {1, 4}, {0, 8},
	{4, 1}, {4, 4}, {4, 7},
	{8, 0}, {7, 4}, {8, 8} };
girandola_size = sizeof girandola / sizeof * girandola;

// prints the grid in a convenient format
char intchar(int num) {
	if (num == 0)
		return '0';
	return num + '0';
}
void print_grid1(int grid[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			printf("%2d", grid[row][col]);
		}
		printf("\n");
	}
}
void print_dash(int num) {
	int i;
	for (i = 0; i < (int)(1.4 * num); i++)
		printf("- ");
	printf("\n");
}
void print_grid2(int grid[N][N]) {
	for (int i = 0; i < N; i++) {
		if (i % n == 0 && i != 0) {
			print_dash(N);
		}
		for (int j = 0; j < N; j++) {
			if (j % n == 0 && j != 0) {
				printf("| ");
			}
			if (j + 1 == N) {
				printf("%c", intchar(grid[i][j]));
				printf("\n");
			}
			else {
				printf("%c", intchar(grid[i][j]));
				if (grid[i][j] < 10)
					printf(" ");
				else
					printf(" ");
			}
		}
	}
	printf("\n");
}
void copygrid(int grid1[N][N], int grid2[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			grid1[i][j] = grid2[i][j];
		}
	}
}

// color scheme for each sudoku variant
void x_color(int grid[N][N], int row, int col) {
	if (row == col || row == (N - 1) - col) {
		for (row = 0; row < N; row++) {
			strcpy(KCOL, KRED);
		}
		for (row = N - 1; row >= 0; row--) {
			strcpy(KCOL, KRED);
		}
	}
	else
		strcpy(KCOL, KWHITE);
}
void dot_color(int grid[N][N], int row, int col) {
	if (row % 3 == 1 && col % 3 == 1) {
		for (row = 1; row < N; row += 3) {
			for (col = 1; col < N; col += 3) {
				strcpy(KCOL, KGREEN);
			}
		}
	}
	else
		strcpy(KCOL, KWHITE);
}
void hyper_color(int grid[N][N], int row, int col) {
	if (row > 0 && row <= 3 && col > 0 && col <= 3 ||
		row > 0 && row <= 3 && col > 4 && col <= 7 ||
		row > 4 && row <= 7 && col > 4 && col <= 7 ||
		row > 4 && row <= 7 && col > 0 && col <= 3) {
		strcpy(KCOL, KBLUE);
	}
	else
		strcpy(KCOL, KWHITE);
}
void parity_color(int grid[N][N], int row, int col) {
	int i;
	for (i = 0; i < parity_size; i++) {
		if (parity[i][0] == row && parity[i][1] == col) {
			strcpy(KCOL, KMAGENTA);
			break;
		}
		else
			strcpy(KCOL, KWHITE);
	}
} 
void argyle_color(int grid[N][N], int row, int col) {
	if (row == col + 1 || row == col - 1 ||
		row == col + 4 || row == col - 4  ||
		row == (N - 1) - col - 1 || row == (N - 1) - col + 1 ||
		row == (N - 1) - col - 4 || row == (N - 1) - col + 4) {
		strcpy(KCOL, KCYAN);
	}
	else {
		strcpy(KCOL, KWHITE);
	}
}
void asterisk_color(int grid[N][N], int row, int col) {
	int i;
	for (i = 0; i < asterisk_size; i++) {
		if (row == asterisk[i][0] && col == asterisk[i][1]) {
			strcpy(KCOL, KICE);
			break;
		}
		else strcpy(KCOL, KWHITE);
	}
}
void girandola_color(int grid[N][N], int row, int col) {
	int i;
	for (i = 0; i < girandola_size; i++) {
		if (row == girandola[i][0] && col == girandola[i][1]) {
			strcpy(KCOL, KDORANGE);
			break;
		}
		else strcpy(KCOL, KWHITE);
	}
}
void offset_color(int grid[N][N], int row, int col) {
	if (row % n == 0 && col % n == 0) {
		strcpy(KCOL, KRED);
	}
	else if (row % n == 0 && col % n == 1) {
		strcpy(KCOL, KBLUE);
	}
	else if (row % n == 0 && col % n == 2) {
		strcpy(KCOL, KGREEN);
	}
	else if (row % n == 1 && col % n == 0) {
		strcpy(KCOL, KCYAN);
	}
	else if (row % n == 1 && col % n == 1) {
		strcpy(KCOL, KYELLOW);
	}
	else if (row % n == 1 && col % n == 2) {
		strcpy(KCOL, KMAGENTA);
	}
	else if (row % n == 2 && col % n == 0) {
		strcpy(KCOL, KPLUM);
	}
	else if (row % n == 2 && col % n == 1) {
		strcpy(KCOL, KDORANGE);
	}
	else if (row % n == 2 && col % n == 2) {
		strcpy(KCOL, KICE);
	}
}

void typecolor(int grid[N][N], int row, int col, char type[]) {
	if (strcmp(_strlwr(type), "x") == 0)
		x_color(grid, row, col);
	else if (strcmp(_strlwr(type), "dot") == 0)
		dot_color(grid, row, col);
	else if (strcmp(_strlwr(type), "hyper") == 0)
		hyper_color(grid, row, col);
	else if (strcmp(_strlwr(type), "even") == 0 || strcmp(_strlwr(type), "odd") == 0)
		parity_color(grid, row, col);
	else if (strcmp(_strlwr(type), "argyle") == 0)
		argyle_color(grid, row, col);
	else if (strcmp(_strlwr(type), "asterisk") == 0)
		asterisk_color(grid, row, col);
	else if (strcmp(_strlwr(type), "girandola") == 0)
		girandola_color(grid, row, col);
	else if (strcmp(_strlwr(type), "offset") == 0)
		offset_color(grid, row, col);
	else
		strcpy(KCOL, KWHITE);
}
void print_gridcolor(int grid[N][N], char type[]) {
	for (int i = 0; i < N; i++) {
		if (i % n == 0 && i != 0) {
			print_dash(N);
		}
		for (int j = 0; j < N; j++) {
			if (j % n == 0 && j != 0) {
				printf("| ");
			}

			typecolor(grid, i, j, type);

			if (j + 1 == N) {
				printf("%s%c%s", KCOL, intchar(grid[i][j]), KWHITE);
				printf("\n");
			}
			else {
				printf("%s%c%s", KCOL, intchar(grid[i][j]), KWHITE);
				if (grid[i][j] < 10)
					printf(" ");
				else
					printf(" ");
			}
		}
	}
	printf("\n");
}

int main() {
	// blank sudoku grid templates
	char blank_9cgrid[N][N] = {
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
	};
	int blank_9igrid[N][N] = {
		//   0  1  2  3  4  5  6  7  8
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
	};
	/*int blank_16igrid[N][N] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};*/

	// grids to solve and analyze
	int grid1[N][N] = {
	//	 0  1  2  3  4  5  6  7  8
		{0, 0, 0, 0, 0, 0, 0, 0, 5}, // 0
		{0, 1, 0, 0, 0, 0, 7, 0, 0}, // 1
		{7, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
		{0, 0, 0, 0, 7, 0, 0, 5, 9}, // 3
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
		{4, 2, 0, 0, 9, 0, 0, 0, 0}, // 5
		{0, 0, 0, 0, 0, 0, 0, 0, 8}, // 6
		{0, 0, 1, 0, 0, 0, 0, 7, 0}, // 7
		{8, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
	};
	char grid2[N][N] = {
	{'0', '0', '0', '0', '1', '5', '7', '3', '4'},
	{'4', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'0', '5', '0', '6', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '0', '0', '0', '7'},
	{'0', '0', '0', '0', '8', '3', '0', '0', '0'},
	{'0', '0', '0', '0', '0', '2', '8', '0', '0'},
	{'2', '7', '7', '0', '0', '0', '3', '9', '0'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0'},
	{'0', '0', '0', '0', '2', '0', '1', '0', '0'},
	};
	/*int grid16by16[N][N] = {
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};*/

	int chosen_grid[N][N];
	char chosen_type[] = "dot";
	int cnum = 6;
	int crow = 1;
	int ccol = 8;

	// print chosen sudoku grid on console
	copygrid(chosen_grid, blank_9igrid);
	printf("Given sudoku grid\n");
	print_gridcolor(chosen_grid, chosen_type);

	// checks if current grid is incompatible
	/*
	if (digit_safe(chosen_grid, crow, ccol, chosen_type) == 1)
		printf("The digit %d at (%d, %d) is safe for a %s sudoku grid.\n", 
			chosen_grid[crow][ccol], crow, ccol, chosen_type);
	else
		printf("The digit %d at (%d, %d) is barred for a %s sudoku grid.\n", 
			chosen_grid[crow][ccol], crow, ccol, chosen_type);*/

	//checks if digit is safe for given condition
	if (!is_exist_nc(chosen_grid, crow, ccol, cnum))
		printf("The number %d is safe at (%d, %d) for %s sudoku.\n",
			cnum, crow, ccol, chosen_type);
	else
		printf("The number %d is barred at (%d, %d) for %s sudoku.\n",
			cnum, crow, ccol, chosen_type);

	// solve sudoku grid
	if (solve(chosen_grid, chosen_type)) {
		printf("%sSolution for %s sudoku grid, %d iterations\n", KWHITE, chosen_type, iteration);
		print_gridcolor(chosen_grid, chosen_type);
	}
	else
		printf("no solution for %s sudoku grid\n", chosen_type);

	printf("Awesome!\n");
	return 0;
}