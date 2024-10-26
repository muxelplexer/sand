#include "world.h"
#include "raylib.h"
#include "assert.h"

#define PART_WIDTH 10

bool* world_cell(struct world* world, const int x, const int y)
{
    assert(x < GRID_SIZE);
    assert(y < GRID_SIZE);
    return &world->grid[(y * GRID_SIZE) + x];
}

void world_update(struct world* world)
{
    bool* cell = nullptr;
    for (int j = GRID_SIZE - 1 ; j >= 0; --j)
    {
        for (int i = GRID_SIZE - 1; i >= 0; --i)
        {
            cell = world_cell(world, i, j);
            if (*cell)
            {
                *world_cell(world, i, j + 1) = true;
                *cell = false;
            }
        }
    }
}

void world_render(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            Color col;
            if (world_cell(world, i, j))
            {
                col = BLACK;
            } else
            {
                col = RAYWHITE;
            }

            DrawRectangle(i * PART_WIDTH, j * PART_WIDTH, PART_WIDTH, PART_WIDTH, col);
        }
    }
}
