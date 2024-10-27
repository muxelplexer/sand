#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#include "world.h"


int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "sand");

    struct world* the_world = malloc(sizeof(struct world));
    memset(the_world, 0, sizeof(struct world));

    SetTargetFPS(120);
    while(!WindowShouldClose())
    {
        world_handle_input(the_world);
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

