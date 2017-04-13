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
    struct dim *dim = enter_dim(6, 6);
    struct root *list = createList();
    printBoard(list, dim);
    delete_list(list);
}
