#pragma once

#define GRID_SIZE  100
struct world
{
    bool grid[GRID_SIZE * GRID_SIZE];
};

void world_update(struct world* world);
void world_render(struct world* world);
