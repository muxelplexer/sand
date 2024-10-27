#pragma once

#define GRID_SIZE  100
struct world_pos
{
    int x;
    int y;
};
struct world_change
{
    struct world_pos src_pos;
    struct world_pos dst_pos;
    struct world_change* next;
};

struct world_change_list
{
    struct world_change* change;
    struct world_change* head;
};

struct world
{
    bool grid[GRID_SIZE * GRID_SIZE];
    struct world_change_list changes;
};

void world_update(struct world* world);
void world_handle_input(struct world* world);
void world_render(struct world* world);
