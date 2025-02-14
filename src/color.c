#include "visualizer.h"

void assign_colors_and_set_min_max(t_vars *vars) {
	t_node	*node;
	
    if (!vars) return;
	node = vars->stack_a;
    while (node) {
        if (node->value <= vars->min)
			vars->min = node->value;
        if (node->value > vars->max)
			vars->max = node->value;
        node = node->next;
    }

    node = vars->stack_a;
    while (node)
	{
        node->color = get_bar_color(node->value, COLOR_VIOLET, COLOR_RED, vars->max);
        node = node->next;
    }
}

int	get_bar_color(int input, int start_color, int end_color, int max)
{
	return ((end_color - start_color) * input / max + start_color);
}
