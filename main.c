//
//  main.c
//  Atoms
//
//  Created by Mohammed Istiaq Ullah on 2017-03-18.
//  Copyright © 2017 Mohammed Istiaq Ullah. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "Atoms.h"

int main(int argc, const char * argv[]) {
  char *instruct = "Input your x and y coordinates to choose which grid to place your atom into,\n"
                    "and own all grid spaces to win. Start by selecting the dimensions you want to\n";
  int x;
  int y;
  printf("%s", instruct);
  printf("\nEnter x and y dimensions ranging from 5 to 10: \n");
  scanf("%d %d", &x, &y);

  struct dim *dimensions = enter_dim(x, y);
  struct root *list = createList();
  int order=1;

  while (order) {

    printBoard(list, dimensions);
    char *player1 = "Player 1";
    char *player2 = "Player 2";
    char *currPlayer;
    char player;

    if (order%2) {
      currPlayer = player1;
      player = 'R';
    } else {
      currPlayer = player2;
      player = 'G';
    }

    printf("%s enter your x coordinate less than %d and y coordinate less than %d: \n", currPlayer, dimensions->xDim, dimensions->yDim);
    scanf("%d %d", &x, &y);

    bool val = addAtom(list, player, x, y, false);
    ++order;

    if (val) {
      printf("%s wins!\nGame ended.", currPlayer);
      return 0;
    }

  }

}
