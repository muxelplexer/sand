#pragma once

typedef enum cell_type
{
    CT_EMPTY,
    CT_SAND,
    CT_WATER
} cell_type_t;

typedef struct cell
{
    enum cell_type type;
} cell_t;

struct world;
void cell_action_sand(struct world* world, const int x, const int y);
