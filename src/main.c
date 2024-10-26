#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#include "world.h"


int main(void)
{
    InitWindow(800, 800, "sand");

    struct world* the_world = malloc(sizeof(struct world));
    memset(the_world, 0, sizeof(struct world));

    the_world->grid[0] = true;
    the_world->grid[100] = true;
    the_world->grid[101] = true;
    the_world->grid[2050] = true;

    SetTargetFPS(120);
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            world_render(the_world);
        EndDrawing();
        world_update(the_world);
    }

    free(the_world);
    CloseWindow();
    return EXIT_SUCCESS;
}

