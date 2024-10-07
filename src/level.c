// Created by Egeyae on 07/10/24.

#include "level.h"
#include <stdlib.h>
#include <time.h>
#include "logging.h"

// Converts x, y coordinates to a 1D array index
int xy_to_index(int x, int y, int width) {
    return (y * width) + x;
}

void buildCorridor(int *map, Room *startRoom, Room *endRoom, int width, int height) {
    log(LOG_INFO, "Building corridor between rooms", 1);

    if (map == NULL || startRoom == NULL || endRoom == NULL) {
        log(LOG_ERROR, "Invalid input for building corridor", 0);
        return;
    }

    int x1 = startRoom->x;
    int y1 = startRoom->y;
    int x2 = endRoom->x;
    int y2 = endRoom->y;

    // Horizontal path first
    int x = x1;
    while (x != x2) {
        int index = xy_to_index(x, y1, width);
        map[index] = FLOOR;
        if (x < x2) {
            x++;
        } else {
            x--;
        }
    }

    // Vertical path second
    int y = y1;
    while (y != y2) {
        int index = xy_to_index(x2, y, width);
        map[index] = FLOOR;
        if (y < y2) {
            y++;
        } else {
            y--;
        }
    }

    log(LOG_INFO, "Corridor built successfully", 1);
}

void recurGenMap(Room *curr_room, int *visited_indexes, int depth, int width, int height, int *map) {
    if (depth == 0) {
        return;
    }

    int rightRoom_chance = rand() % curr_room->chance < 20;
    int x, y;
    int out = 0;

    while (out == 0) {
        x = 10 + rand() % (width - 10);
        y = 10 + rand() % (height - 10);

        if (visited_indexes[xy_to_index(x, y, width)] == 0) {
            visited_indexes[xy_to_index(x, y, width)] = 1;
            Room *leftRoom = malloc(sizeof(Room));
            if (leftRoom == NULL) {
                log(LOG_ERROR, "Failed to allocate left room", 0);
                exit(-1);
            }
            leftRoom->x = x;
            leftRoom->y = y;
            leftRoom->chance = 100;
            curr_room->nextLeft = leftRoom;

            recurGenMap(leftRoom, visited_indexes, depth - 1, width, height, map);

            buildCorridor(map, curr_room, leftRoom, width, height);
            out = 1;
        }
    }

    if (rightRoom_chance) {
        int out1 = 0;
        while (out1 == 0) {
            x = 10 + rand() % (width - 10);
            y = 10 + rand() % (height - 10);
            if (visited_indexes[xy_to_index(x, y, width)] == 0) {
                visited_indexes[xy_to_index(x, y, width)] = 1;
                Room *rightRoom = malloc(sizeof(Room));
                if (rightRoom == NULL) {
                    log(LOG_ERROR, "Failed to allocate right room", 0);
                    exit(-1);
                }
                rightRoom->x = x;
                rightRoom->y = y;
                rightRoom->chance = curr_room->chance + 40;
                curr_room->nextRight = rightRoom;

                recurGenMap(rightRoom, visited_indexes, depth - 1, width, height, map);
                buildCorridor(map, curr_room, rightRoom, width, height);
                out1 = 1;
            }
        }
    }
}

void generateMap(struct Level *level) {
    log(LOG_INFO, "Generating map", 0);

    if (level == NULL || level->map == NULL) {
        log(LOG_ERROR, "Level or map is NULL. Cannot generate map.", 0);
        return;
    }

    srand(time(NULL));

    int *visited_indexes = malloc(sizeof(int) * level->width * level->height);

    if (visited_indexes == NULL) {
        log(LOG_ERROR, "Cannot allocate memory for visited_indexes.", 0);
        return;
    }

    for (int i = 0; i < level->width * level->height; i++) {
        visited_indexes[i] = 0;
    }

    Room *startRoom = malloc(sizeof(Room));
    if (startRoom == NULL) {
        log(LOG_ERROR, "Failed to allocate start room", 0);
        free(visited_indexes);
        return;
    }

    startRoom->x = level->width/2;
    startRoom->y = level->height/2;
    startRoom->chance = 100;
    startRoom->nextLeft = NULL;
    startRoom->nextRight = NULL;

    visited_indexes[xy_to_index(startRoom->x, startRoom->y, level->width)] = 1;

    recurGenMap(startRoom, visited_indexes, 5, level->width, level->height, level->map);

    free(startRoom);
    free(visited_indexes);

    log(LOG_INFO, "Map generation complete", 0);
}

int levelInit(struct Level *level, int width, int height, int depth) {
    log(LOG_DEBUG, "Initializing level", 0);

    level->width = width;
    level->height = height;
    level->depth = depth;

    log(LOG_DEBUG, "Allocating memory for level map", 1);
    level->map = malloc((level->height * level->width) * sizeof(int));

    if (level->map == NULL) {
        log(LOG_ERROR, "Failed to allocate memory for level map", 1);
        return -1;
    }

    for (int i = 0; i < level->height * level->width; i++) {
        level->map[i] = EMPTY;
    }

    log(LOG_DEBUG, "Level initialized", 0);
    return 0;
}

void levelFree(struct Level *level) {
    if (level != NULL) {
        free(level->map);
        free(level);
        log(LOG_DEBUG, "Level memory freed", 0);
    }
}

struct Level *levelCreate(int width, int height, int depth) {
    log(LOG_INFO, "Creating new level", 0);

    struct Level *level = malloc(sizeof(struct Level));
    if (level == NULL) {
        log(LOG_ERROR, "Failed to allocate memory for level", 0);
        return NULL;
    }

    if (levelInit(level, width, height, depth) == -1) {
        log(LOG_ERROR, "Failed to initialize level", 0);
        free(level);
        return NULL;
    }

    log(LOG_INFO, "Level created successfully", 0);
    return level;
}
