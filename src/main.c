#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define PART_WIDTH 10
#define GRID_SIZE  100

struct world
{
    bool grid[GRID_SIZE * GRID_SIZE];
};

void world_render(struct world* world);

int main(void)
{
    InitWindow(800, 800, "sand");

    struct world the_world;
    memset(&the_world, 0, sizeof(struct world));

    the_world.grid[0] = true;
    the_world.grid[100] = true;
    the_world.grid[101] = true;
    the_world.grid[200] = true;

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            world_render(&the_world);
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}

void world_render(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            Color col;
            if (world->grid[(j * GRID_SIZE) + i])
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
