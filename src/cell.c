#include "cell.h"
#include "world.h"

void cell_action_sand(struct world* world, const int x, const int y)
{
    bool below_cell = world_cell_is_empty(world, x, y + 1);
    bool lb_cell = world_cell_is_empty(world, x - 1, y + 1);
    bool rb_cell = world_cell_is_empty(world, x + 1, y + 1);

    if (below_cell)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x, y + 1};
        world_cell_move(world, src, dst);
    } else if (lb_cell)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x - 1, y + 1};
        world_cell_move(world, src, dst);
    } else if (rb_cell)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x + 1, y + 1};
        world_cell_move(world, src, dst);
    }
}
