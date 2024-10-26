#include <stdlib.h>
#include "raylib.h"

int main(void)
{
    InitWindow(800, 800, "sand");
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}
