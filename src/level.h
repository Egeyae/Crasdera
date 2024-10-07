//
// Created by Egeyae on 07/10/24.
//

#ifndef LEVEL_H
#define LEVEL_H

typedef enum TileType {
    EMPTY,
    WALL,
    FLOOR
} TileType;

struct Level {
    int depth;
    int width;
    int height;
    int *map;
};

typedef struct RoomNode {
    int x;
    int y;
    int chance;
    struct RoomNode *nextLeft; // most likely
    struct RoomNode *nextRight; // least likely
} Room;

void generateMap(struct Level *level);
void levelFree(struct Level *level);
int xy_to_index(int x, int y, int width);
#endif //LEVEL_H
