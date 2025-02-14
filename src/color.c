#include "visualizer.h"

// Estructura para representar un color en formato RGB
typedef struct {
	int r, g, b;
} Color;

// Función para convertir HSL a RGB
Color hsl_to_rgb(float h, float s, float l) {
	float c = (1.0 - fabs(2.0 * l - 1.0)) * s;
	float x = c * (1.0 - fabs(fmod(h / 60.0, 2) - 1.0));
	float m = l - c / 2.0;
	float r, g, b;

	if (h < 60) {
		r = c;
		g = x;
		b = 0;
	} else if (h < 120) {
		r = x;
		g = c;
		b = 0;
	} else if (h < 180) {
		r = 0;
		g = c;
		b = x;
	} else if (h < 240) {
		r = 0;
		g = x;
		b = c;
	} else if (h < 300) {
		r = x;
		g = 0;
		b = c;
	} else {
		r = c;
		g = 0;
		b = x;
	}

	Color color;
	color.r = (r + m) * 255;
	color.g = (g + m) * 255;
	color.b = (b + m) * 255;

	return color;
}

int rgb_to_hex_int(Color color) {
	return ((color.r << 16) | (color.g << 8) | color.b);
}

int get_color(int value, int minValue, int maxValue) {
	float h = ((float)value / (maxValue - minValue)) * 360;
	Color color = hsl_to_rgb(h, 1.0, 0.5);
	return rgb_to_hex_int(color);
}

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
        node->color = get_color(node->value, vars->min, vars->max);
		node = node->next;
    }
}
