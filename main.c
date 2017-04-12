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

void printList(struct root *list){
    struct atom *node = list->first;
    while (node) {
        printf("%c%d (%d, %d)\n", node->player, node->atoms, node->x, node->y);
        node = node->next;
    }
}
/* I tested a couple of cases
test more thoroughly to see if it works*/
int main(int argc, const char * argv[]) {
    struct dim *dim = enter_dim(6, 6);
    struct root *list = createList();
    //addAtom(list, 'R', 0, 1, false);
    printBoard(list, dim);
    //printList(list);
    //printf("%d\n", list->length);
}
