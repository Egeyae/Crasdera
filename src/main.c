//
// Created by Egeyae on 07/10/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "level.h"


int main(int argc, const char * argv[]) {
    struct Level *level = malloc(sizeof(struct Level));
    generateMap(level);

    for (int x = 0; x < level->width; x++) {
        for (int y = 0; y < level->height; y++) {
            switch (level->map[xy_to_index(x, y, level->width)]) {
                case EMPTY:
                    printf(" ");
                case WALL:
                    printf("#");
                case FLOOR:
                    printf(".");
                default:
                    printf("ð");
            }

        }
        printf("\n");
    }

    levelFree(level);
    return 0;
}