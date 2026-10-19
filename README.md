# Multi-Sudoku Console

[Project portfolio](https://fyemane.github.io/projects.html) · [About me, experience & qualifications](https://fyemane.github.io/)


My Windows console Sudoku solver written in C with a Visual Studio project. I built it to explore recursive backtracking and how a common solving algorithm can be extended with different Sudoku constraints.

The program works with a 9 × 9 integer grid, uses `0` for empty cells, and prints the starting grid followed by the first solution it finds. Console colours highlight cells associated with the selected variant.

**Status: work in progress.** The repository contains several variant implementations, but they haven't all been fully validated. Some known limitations are listed below.

## Features

- Recursive backtracking with row, column, and 3 × 3 box checks.
- Additional rule functions for diagonal, region, parity, and adjacency variants.
- Colour-coded console output and 3 × 3 box separators.
- Support for partially filled grids or a blank grid.
- A counter reporting failed search branches during solving.
- Editable cell-coordinate lists for the parity, asterisk, and girandola patterns.

## Variant guide

These are the intended rules represented by the source. Standard row, column, and box uniqueness checks are applied before the selected variant rule.

| `chosen_type` | Additional rule |
| --- | --- |
| `"normal"` | Standard Sudoku only; this uses the current fallback path |
| `"x"` | Both main diagonals contain unique digits |
| `"dot"` | The nine centre cells of the 3 × 3 boxes form an additional unique-digit region |
| `"hyper"` | Four additional 3 × 3 regions contain unique digits |
| `"odd"` | Cells listed in `parity` must contain odd digits |
| `"even"` | Cells listed in `parity` must contain even digits |
| `"argyle"` | The selected offset diagonals contain unique digits |
| `"asterisk"` | The nine cells listed in `asterisk` form an additional region |
| `"girandola"` | The nine cells listed in `girandola` form an additional region |
| `"offset"` | Cells in the same relative position across the nine boxes form an additional region |
| `"non-consecutive"` or `"nc"` | Orthogonally adjacent filled cells should not contain consecutive values; implementation is incomplete |

Only one variant string is selected at a time. The current program doesn't combine several variant rules through a menu or command-line options.

## How the solver works

1. Find the first empty cell by scanning the grid row by row.
2. Try candidate digits from `1` through `9`.
3. Check the row, column, box, and selected variant constraints.
4. Place a valid candidate and recursively solve the next empty cell.
5. If the branch fails, reset the cell to `0` and try the next candidate.
6. Return when the grid is filled or all candidates have been exhausted.

The solver modifies the working grid in place and stops at the **first solution**. It doesn't enumerate solutions or establish that a puzzle has a unique solution.

The `iteration` variable starts at `1` and is incremented when a recursive call exhausts its candidates. Although the console labels it as iterations, it isn't a count of every candidate test or recursive call.

## Building and running

The checked-in solution targets Windows, the Visual Studio **v143 C++ toolset**, and Windows SDK 10.0. It includes Win32/x64 and Debug/Release configurations. No external solver or graphics library is required.

1. Clone or download the repository.
2. Open `Sudoku.sln` in Visual Studio with the Desktop development with C++ tools installed.
3. Select the desired platform and configuration, and inspect the build notes below if the current source fails to compile.
4. Configure the puzzle in `main.c`.
5. Build and run the console application. Use an ANSI-colour-capable terminal if escape codes appear instead of coloured digits.

The `Debug` folder contains historical build outputs. Those files don't establish that the current source rebuilds unchanged.

## Choosing a puzzle

The current setup is **source-configured**, with no interactive puzzle-entry interface.

Near the bottom of `main.c`, choose the rule string and the grid passed to `copygrid()`:

```c
int chosen_grid[N][N];
char chosen_type[] = "dot";

copygrid(chosen_grid, blank_9igrid);
```

That is the checked-in default: a blank grid using the Dot rule. To solve the existing integer puzzle instead, change the copy call to:

```c
copygrid(chosen_grid, grid1);
```

Edit `grid1` or add another `int` array with nine rows of nine values. Use `1`–`9` for clues and `0` for blanks. Keep `chosen_type` as a writable character array because the source lowercases it in place with `_strlwr()`.

The `parity`, `asterisk`, and `girandola` arrays use **zero-based row/column coordinates**. Their entries determine which cells receive the extra constraint and colour highlighting.

## Source layout

| File | Purpose |
| --- | --- |
| `main.c` | Puzzle definitions, variant patterns, console formatting, and program entry point |
| `sudoku.c` | Empty-cell search, constraint checks, and recursive solver |
| `mycolors.c` | ANSI colour definitions and colour helpers |
| `Header.h` | Additional basic colour-printing helpers |
| `Sudoku.sln` / `Sudoku.vcxproj` | Visual Studio solution and project settings |
| `Debug/` | Previously generated binaries and compiler/debug output |

## Current limitations

- The grid size is fixed to 9 × 9. Commented 16 × 16 experiments aren't active support for larger puzzles.
- Initial clues aren't comprehensively validated before solving. A fully filled invalid board can reach the solver's completion condition without a separate validity check.
- The X-rule checker uses an `if`/`else if` structure, so the centre cell doesn't check both diagonals.
- Non-consecutive checking currently covers only the top row and doesn't consistently exclude empty neighbours. Argyle indexing also needs boundary review.
- Several global definitions omit explicit types, and `_strlwr()` is Microsoft-specific. These details need attention for stricter compilers or a Linux/macOS port.
- `main.c` directly includes `mycolors.c` and `sudoku.c`, while the Visual Studio project also lists them as compilation units. Build organisation needs review to avoid duplicate-definition issues.
- Unrecognised variant strings fall back to standard checks rather than producing an input error.

This README documents the existing implementation. A fresh build and full variant-correctness test have not been performed as part of this documentation update.

## Credits

The original solver reference linked in `main.c` is [this backtracking Sudoku example](https://gist.github.com/bopbi/c9f94b1b981b84bcb02b). This project explores additional variant constraints and coloured console presentation around that approach. Existing source references are retained.
