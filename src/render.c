#include "visualizer.h"


int draw_bars(t_vars *vars) {
    
    int bar_width, bar_height;
    int i, j, k, x, y;
    int bpp, size_line, endian;
    int separator_x;

    if (!vars->rendering)
        return 0;

    // Ajustar el ancho de las barras
    bar_width = (WIN_WIDTH / (2 * vars->max_size));
    if (bar_width < 1) {
        bar_width = 1;  // Limitar el ancho mínimo de la barra
    }
    separator_x = WIN_WIDTH / 2 - 10;

    // Crear imagen de doble buffer
    void *buffer_img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
    int *buffer_data = (int *)mlx_get_data_addr(buffer_img, &bpp, &size_line, &endian);

    t_node *current_a = vars->stack_a;
    t_node *current_b = vars->stack_b;

    // Dibujar la barra separadora blanca en el buffer
    for (j = 0; j < WIN_HEIGHT; j++) {
        for (k = 0; k < 20; k++) {
            buffer_data[j * (size_line / 4) + (separator_x + k)] = COLOR_WHITE;
        }
    }

    // Ajustar el tamaño de las barras para que se representen correctamente en la ventana
    for (i = 0; current_a != NULL || current_b != NULL; i++) {
        if (current_a != NULL) {
            bar_height = MIN_BAR_HEIGHT + (MAX_BAR_HEIGHT - MIN_BAR_HEIGHT) * ((double)(current_a->value - vars->min) / (vars->max - vars->min));
            y = i * bar_width;
            x = (WIN_WIDTH / 2) - separator_x;  
            for (j = 0; j < bar_width; j++) {
                for (k = 0; k < bar_height; k++) {
                    buffer_data[(y + j) * (size_line / 4) + k] = current_a->color;
                }
            }
            current_a = current_a->next;
        }

        if (current_b != NULL) {
            bar_height = MIN_BAR_HEIGHT + (MAX_BAR_HEIGHT - MIN_BAR_HEIGHT) * ((double)(current_b->value - vars->min) / (vars->max - vars->min));
            y = i * bar_width;  // Dibujar de arriba hacia abajo
            x = separator_x + 20;
            for (j = 0; j < bar_width; j++) {
                for (k = 0; k < bar_height; k++) {
                    buffer_data[(y + j) * (size_line / 4) + (x + k)] = current_b->color;
                }
            }
            current_b = current_b->next;
        }
    }

    // Copiar el buffer a la ventana
    mlx_put_image_to_window(vars->mlx, vars->win, buffer_img, 0, 0);
    mlx_destroy_image(vars->mlx, buffer_img);

    // Dibujar nombres de los stacks
    mlx_string_put(vars->mlx, vars->win, 10, WIN_HEIGHT - 20, COLOR_WHITE, "Stack A");
    mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 2 + 30, WIN_HEIGHT - 20, COLOR_WHITE, "Stack B");

    return 0;
}

void draw_counter(t_vars *vars) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Operations: %d", vars->move_count);
    int x = WIN_WIDTH - 200;
    int y = WIN_HEIGHT - 40;
    mlx_string_put(vars->mlx, vars->win, x + 2, y + 2, COLOR_WHITE, buffer);
}
