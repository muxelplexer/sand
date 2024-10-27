#pragma once

enum cell_type
{
    CT_EMPTY,
    CT_SAND
};

typedef struct cell
{
    enum cell_type type;
} cell_t;
