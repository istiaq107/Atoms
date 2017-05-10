#include "Atoms.h"



const int cornerLimit = 2;
const int sideLimit = 3;
const int otherLimit = 4;

struct dim dimensions;

struct dim *enter_dim(int x, int y){
    dimensions.xDim = x;
    dimensions.yDim = y;
    return &dimensions;
}

struct root *createList(){
    struct root *list = malloc(sizeof(struct root));
    list->first = NULL;
    list->length = 0;
    return list;
}

struct atom *createAtom(char player, int x, int y, int limit){
    struct atom *position = malloc(sizeof(struct atom));
    position->player = player;
    position->x = x;
    position->y = y;
    position->limit = limit;
    position->atoms = 1;
    return position;
}

int assignLimit(int x, int y){

    int xMax = dimensions.xDim - 1;
    int yMax = dimensions.yDim - 1;

    if ((x == 0 && y == 0) || (x == 0 && y == xMax) ||(y == 0 && x == xMax) || (y == yMax && x == xMax)) return cornerLimit;

    if (x == 0 || y == 0 || x == xMax || y == yMax) return sideLimit;

    return otherLimit;
}

struct atom *atomPresent(struct root *list, int x, int y){
    struct atom *node = list->first;

    while (node) {
        if (node->x == x && node->y == y) return node;
        node = node->next;
    }

    return NULL;
}

void deleteAtom(struct root *list, struct atom *position){
    --(list->length);
    struct atom *node = list->first;

    if (node->x == position->x && node->y == position->y) {
        struct atom *remove = node;
        list->first=node->next;
        free(remove);
        remove = NULL;
        return;
    }

    while (node && node->next) {
        if (node->next->x == position->x && node->next->y == position->y) {
            struct atom *remove = node->next;
            node->next=remove->next;
            free(remove);
            remove = NULL;
            return;
        }
        node = node->next;
    }
}

bool addAtom(struct root *list, char player, int x, int y, bool chain){
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
            if (list->length > (dimensions.xDim * dimensions.yDim)) return true; /* This is to stop the chain reaction when grid is filled*/
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

    }
    return false;
}

void delete_list(struct root *list){
	struct atom *current = list->first;

	while (current) {
		struct atom *delete = current;
		current = current->next;
		free(delete);
	}
	free(list);
}

void printBoard(struct root *list, struct dim *dim){
    int xMax = dim->xDim;
    int yMax = dim->yDim;
    int len = xMax * 3 - 1;

    printf("+");
    for (int i=0; i<len; ++i) {
        printf("-");
    }
    printf("+\n");

    for (int i=0; i<yMax; ++i) {
        for (int j=0; j<xMax; ++j) {
            struct atom *node = list->first;
            bool notOccupied = true;

            while (node) {
                if (node->y == i && node->x == j) {
                    printf("|%c%d", node->player, node->atoms);
                    notOccupied = false;
                    break;
                }
                node=node->next;
            }

            if (notOccupied) {
                printf("|  ");
            }
        }
        printf("|\n");
    }

    printf("+");
    for (int i=0; i<len; ++i) {
        printf("-");
    }
    printf("+\n\n");
}
