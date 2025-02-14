#include "visualizer.h"

int draw_bars(t_vars *vars) {
	
	int bar_width, bar_height;
    int i, j, k, x, y;
    void *img;
    int *img_data;
    int bpp, size_line, endian;
	
    if (!vars->rendering)
        return 0;
    bar_width = (WIN_HEIGHT / vars->max_size) * 0.8;
    mlx_clear_window(vars->mlx, vars->win);

    t_node *current_a = vars->stack_a;
    t_node *current_b = vars->stack_b;

    for (i = 0; current_a != NULL || current_b != NULL; i++) {
        if (current_a != NULL) {
			bar_height = (WIN_WIDTH / 2) * 0.8 * ((double)(current_a->value - vars->min) / (vars->max - vars->min));
			if (bar_height <= 0)
				bar_height = 1;
            y = i * bar_width;
            x = (WIN_WIDTH / 2) - bar_height;
            img = mlx_new_image(vars->mlx, bar_height, bar_width);
            img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
            for (j = 0; j < bar_width; j++) {
                for (k = 0; k < bar_height; k++) {
                    img_data[j * (size_line / 4) + k] = current_a->color;
                }
            }
            mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
            mlx_destroy_image(vars->mlx, img);
            current_a = current_a->next;
        }

        if (current_b != NULL) {
			bar_height = (WIN_WIDTH / 2) * 0.8 * ((double)(current_b->value - vars->min) / (vars->max - vars->min));
			if (bar_height <= 0)
				bar_height = 1;
            y = i * bar_width;
            x = WIN_WIDTH / 2;
            img = mlx_new_image(vars->mlx, bar_height, bar_width);
            img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
            for (j = 0; j < bar_width; j++) {
                for (k = 0; k < bar_height; k++) {
                    img_data[j * (size_line / 4) + k] = current_b->color;
                }
            }
            mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
            mlx_destroy_image(vars->mlx, img);

            current_b = current_b->next;
        }
    }
    draw_counter(vars);
    return (0);
}


void draw_counter(t_vars *vars) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Operations: %d", vars->move_count);
    int x = WIN_WIDTH - 200;
    int y = WIN_HEIGHT - 40;
    mlx_string_put(vars->mlx, vars->win, x + 2, y + 2, COLOR_WHITE, buffer);
}
