/*do have the structure definitions to make understanding easier*/
void deleteAtom(struct root *list, struct atom *position){
    --(list->length); //first thing, it decreases the length of the list, as the
                      //grid space is being emptied of all the atoms inside it
    struct atom *node = list->first; //node is now the first item in the list

    if (node->x == position->x && node->y == position->y) { //so now that we have
      // the grid space that has to be deleted, we want to check whether the
      // first grid space(the first item in the list) is the same, and we do
      // that by checking the co0ordinates

        struct atom *remove = node; // if it is, we select that and store that
        // in a different variable to be deleted later.
        // if we just delete it right away, the item points to the next item in
        // the list, and we lose that as it falls into eternal abyss and we
        // shall never find any of the other items as they were all linked toge-
        // ther, and now the list is empty, and has no cock to suck
        list->first=node->next; // so what we do is that we make the 'first'
        // pointer and assign it to be the value of the next item to the one we
        // selected, i.e, the list now points to the second item
        free(remove); // we remove the memory allocated for the first item, so
        // now it's as if like the first item never existed, as the 'first'
        // pointer in the list points to the item which was after that.
        remove = NULL; // assign NULL to the declared variable(just standard
        // practice, not exactly necessary)
        return; // stop the function
    }
    // but if the first item is not the required item
    while (node && node->next) { // we go onto check whether the that item, and
      // the next is not NULL
        if (node->next->x == position->x && node->next->y == position->y) { // we
            // already checked the first item whether it had it right, now, we check
            // the one after that the same way.
            struct atom *remove = node->next; // the next
            node->next=remove->next;// steps [#]
            free(remove);// follow
            remove = NULL;// the same idea
            return;// as was done in the if block for the first item
        }
        // but if the next item, i.e the second, wasn't the one we wanted either
        node = node->next; // we make node point to the one after that, i.e the
        // node selected is now the second item, and go back to the while statement
        // if you're wondering, why I'm not checking the node itself, and the next
        // item to it instead, that's because, i'll have to be holding that node,
        // so I can make it's next point to the item after the one found. Simply
        // put, the step marked with [#] won't be able to be done. Ask me this
        // over the phone if it's still confusing. And if you're wondering why
        // check both node and node->next, it's because if I'm actually working
        // with the node->next, right? If i don't check whether it's null or not
        // i'll end up with a seg-fault. And if I do, it stops the while block
        // then and there. So that's how you remove an item/gridspace/node
        // please be advise, that these terms were used interchangably
    }
}


void addAtom(struct root *list, char player, int x, int y, bool chain){
    int limit = assignLimit(x, y);
    struct atom *node = atomPresent(list, x, y);
    if (node && chain) node->player = player;
    if (node == NULL) {
        struct atom *position = createAtom(player, x, y, limit);;
        ++(list->length);
        position->next = list->first;
        list->first = position;

    } else if (node->player == player){
        if (node->atoms+1 < limit) {
            ++(node->atoms);

        } else {
            if (list->length > (dimensions.xDim * dimensions.yDim)) return; /* This is to stop the chain reaction when grid is filled*/
            deleteAtom(list, node);
            int xInc = x + 1;
            int xDec = x - 1;
            int yInc = y + 1;
            int yDec = y - 1;
            if (xInc < dimensions.xDim) addAtom(list, player, x+1, y, true);
            if (xDec > 0) addAtom(list, player, x-1, y, true);
            if (yInc < dimensions.yDim) addAtom(list, player, x, y+1, true);
            if (yDec > 0) addAtom(list, player, x, y+1, true);
        }

    } else {
        /* This executes when the player chooses a grid space that
         is not owned by him*/
        return;
    }
}
