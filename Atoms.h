#ifndef Atoms_h
#define Atoms_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/** Struct definitions **/


/* Holds the dimensions */
struct dim {
    int xDim;
    int yDim;
};


/* all the data in an atom */
struct atom {
    char player;
    int x;
    int y;
    int limit;
    int atoms;
    struct atom *next;
};


/* the starting point of the list */
struct root {
    struct atom *first;
    int length;
};



/** Methods **/


/* Takes in dimensions */
struct dim *enter_dim(int x, int y);

/* Creates the list with 0 items */
struct root *createList();

/* Creates atom with info of grid space */
struct atom *createAtom(char player, int x, int y, int limit);

/* gives limits to grid spaces */
int assignLimit(int x, int y);

/* Checks if atom is present in gridspace, returns grid info if true, null if false */
struct atom *atomPresent(struct root *list, int x, int y);

/* Delete grid spaces and spreads atoms around according to limit */
void deleteAtom(struct root *list, struct atom *position);

/* When an atom is added, adds if grid space empty, or does other stuff */
void addAtom(struct root *list, char player, int x, int y, bool chain);

/* Shows the board */
void printBoard(struct root *list, struct dim *dim);

#endif /* Atoms_h */
