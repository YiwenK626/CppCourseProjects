#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};

typedef struct _board_t board_t;

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines taht we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  //printf("%d, %d\n", b->width, limit);
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while (b->board[y][x] ==
           HAS_MINE);         // if y,x has already been added as mine, try another time
  b->board[y][x] = HAS_MINE;  // if not, add as mine
}

board_t * makeBoard(int w, int h, int numMines) {
  //WRITE ME!
  board_t * b = (board_t *)malloc(sizeof(board_t));
  b->board = malloc(h * sizeof(*b->board));
  int i, j = 0;
  for (j = 0; j < h; j++) {
    b->board[j] = malloc(w * sizeof(*b->board[j]));
    for (i = 0; i < w; i++) {
      b->board[j][i] = UNKNOWN;
    }
  }

  b->width = w;
  b->height = h;
  b->totalMines = numMines;
  for (int m = 0; m < b->totalMines; m++) {
    addRandomMine(b);
  }
  return b;
}
void printBoard(board_t * b) {
  int found = 0;
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y % 100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == KNOWN_MINE) {
        printf("*");
        found++;
      }
      else if (b->board[y][x] < 0) {
        printf("?");
      }
      else if (b->board[y][x] == 0) {
        printf(" ");
      }
      else {
        printf("%d", b->board[y][x]);
      }
    }
    printf("\n");
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");

  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\nFound %d of %d mines\n", found, b->totalMines);
}
int countMines(board_t * b, int x, int y) {
  //WRITE ME!
  int count = 0;

  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (IS_MINE(b->board[ny][nx])) {
          count++;  // count the surrounding mines and itself(which must be safe)
        }
      }
    }
  }

  return count;
}
int click(board_t * b, int x, int y) {
  if (x < 0 || x >= b->width || y < 0 || y >= b->height) {  // not in the board range
    return CLICK_INVALID;
  }
  if (b->board[y][x] == KNOWN_MINE) {  // clicked the known mine
    return CLICK_KNOWN_MINE;
  }
  if (b->board[y][x] == HAS_MINE) {  // clicked the unknown mine - lose
    return CLICK_LOSE;
  }
  if (b->board[y][x] != UNKNOWN) {  // clicked the shown safe cell - continue
    return CLICK_CONTINUE;
  }

  b->board[y][x] = countMines(
      b,
      x,
      y);  // UNKNOWN, i.e. unshown safe cells  -  fill the cell with amount of surrounding mines
  return CLICK_CONTINUE;
}

int checkWin(board_t * b) {
  //WRITE ME!
  int w = b->width;
  int h = b->height;
  int ** board = b->board;
  int i, j, count = 0;
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if (board[j][i] != UNKNOWN) {
        count++;
      }
    }
  }

  if (count == h * w) {
    return 1;
  }
  return 0;
}

void freeBoard(board_t * b) {
  //WRITE ME!
  int j;
  int ** board = b->board;
  for (j = 0; j < b->height; j++) {
    free(board[j]);
  }
  free(board);
  free(b);
}

int readInt(char ** linep, size_t * lineszp) {
  if (getline(linep, lineszp, stdin) == -1) {
    fprintf(stderr, "End of file from keyboard reading a number.  Quitting\n");
    exit(EXIT_FAILURE);
  }
  char * endptr = NULL;
  long int x = strtol(*linep, &endptr, 10);
  if (endptr == *linep) {
    fprintf(stderr, "You did not enter any valid number\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (*endptr != '\n') {
    fprintf(stderr, "Input was not entirely a number (junk at end)\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (x > INT_MAX) {
    fprintf(stderr, "%ld is too big for an int!\n", x);
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  return x;
}

void doReveal(board_t * b, int x, int y, int revealMines) {
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 &&
          ny < b->height) {  // for surroundings within the board
        if (revealMines) {   // if cell value = unknown cells (all remaining are mines)
          assert(b->board[ny][nx] != UNKNOWN);
          if (b->board[ny][nx] == HAS_MINE) {  // turn hiden mines into known mines
            b->board[ny][nx] = KNOWN_MINE;
          }
        }
        else {  // if cell value = known mines (none remaining are mines)
          assert(b->board[ny][nx] !=
                 HAS_MINE);  // make sure remaining cell do not have mines
          if (b->board[ny][nx] == UNKNOWN) {  // turn the remaining into numbers
            b->board[ny][nx] = countMines(b, nx, ny);
          }
        }
      }
    }
  }
}

int maybeReveal(board_t * b, int x, int y) {
  int unknownSquares = 0;
  int knownMines = 0;
  for (int dy = -1; dy <= 1; dy++) {  // for the surrounding of each cell
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 &&
          ny < b->height) {  // if it's in the range of board
        if (b->board[ny][nx] == UNKNOWN ||
            b->board[ny][nx] == HAS_MINE) {  // count total unknown cells
          unknownSquares++;
        }
        else if (b->board[ny][nx] == KNOWN_MINE) {  // count total known mines
          knownMines++;
        }
      }
    }
  }
  assert(knownMines + unknownSquares >= b->board[y][x]);
  assert(knownMines <= b->board[y][x]);
  if (unknownSquares > 0) {  // if there are unknown cells
    int revealMines = (knownMines + unknownSquares == b->board[y][x]);
    int allKnown = knownMines == b->board[y][x];
    if (revealMines ||
        allKnown) {  // either cell value = known mines or unknown cells, i.e. remaining are all safe or all mines
      assert(!revealMines || !allKnown);
      doReveal(b, x, y, revealMines);
      return 1;
    }
  }
  return 0;
}
void determineKnownMines(
    board_t * b) {  // as long as there is a cell that maybeReveal == 1, repeat this step
  int foundMore = 0;
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] >= 0) {
        foundMore = maybeReveal(b, x, y) || foundMore;
      }  // complete when there is unknown cells
    }
  }
  if (foundMore) {  // foundMore = 1, need to found more because there are unknown cells
    determineKnownMines(b);
  }
}

void revealMines(board_t * b) {
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == HAS_MINE) {
        b->board[y][x] = KNOWN_MINE;
      }
    }
  }
}
int playTurn(board_t * b, char ** linep, size_t * lineszp) {
  printf("Current board:\n");
  printBoard(b);
  printf("x coordinate:\n");
  int x = readInt(linep, lineszp);  // read x
  printf("y coordinate:\n");
  int y = readInt(linep, lineszp);  // read y
  int result = click(b, x, y);      // return the property of cell clicked
  determineKnownMines(b);
  if (result == CLICK_LOSE) {
    printf("Oh no! That square had a mine. You lose!\n");
    revealMines(b);
    printBoard(b);
    return 1;
  }
  else if (result == CLICK_INVALID) {
    printf("That is not a valid square, please try again\n");
  }
  else if (result == CLICK_KNOWN_MINE) {
    printf("You already know there is a mine there!\n");
  }
  else if (checkWin(b)) {
    printBoard(b);
    printf("You win!\n");
    return 1;
  }
  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: minesweeper width height numMines\n");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int numMines = atoi(argv[3]);
  if (width <= 0 || height <= 0 || numMines <= 0) {
    fprintf(stderr, "Width, height, and numMines must all be positive ints\n");
    return EXIT_FAILURE;
  }
  char * line = NULL;
  size_t linesz = 0;

  do {
    board_t * b = makeBoard(width, height, numMines);
    int gameOver = 0;
    while (!gameOver) {                        // while the game is not won/lost
      gameOver = playTurn(b, &line, &linesz);  // play the game
    }
    freeBoard(b);  // game ends, free the memory
    do {
      printf("Do you want to play again?\n");
    } while (getline(&line, &linesz, stdin) == -1);
  } while (line[0] == 'Y' || line[0] == 'y');
  free(line);
  return EXIT_SUCCESS;
}
