/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:19:00 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/02/14 04:43:18 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 800

# define COLOR_WHITE	0xFFFFFF
# define COLOR_BLACK	0x000000
# define COLOR_RED		0xFF0000
# define COLOR_GREEN	0x00FF00
# define COLOR_BLUE		0x0000FF
# define COLOR_YELLOW	0xFFFF00
# define COLOR_VIOLET	0x8B00FF

# define VISUALIZER "Visualizer"

typedef struct s_node
{
    int value;
	int	color;
    struct s_node *next;
} t_node;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_node		*stack_a;
	t_node		*stack_b;
	int			min;
	int			max;
	int			max_size;
	int			move_count;
	int			rendering;
}	t_vars;

t_node	*ft_get_last_node(t_node *stack);

void	assign_colors_and_set_min_max(t_vars *vars);
int		get_bar_color(int input, int start_color, int end_color, int max);

int 	draw_bars(t_vars *vars);
void	draw_counter(t_vars *vars);

void 	execute_operation(t_vars *vars, const char *operation);

#endif
