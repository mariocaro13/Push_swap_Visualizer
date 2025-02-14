/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:24:16 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/02/14 02:25:03 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movements.h"

void ft_reverse_rotate(t_node **stack) {
    t_node *first = *stack;
    t_node *last = *stack;
    t_node *second_last = NULL;

    while (last->next != NULL) {
        second_last = last;
        last = last->next;
    }

    if (second_last != NULL) {
        second_last->next = NULL;
    }

    last->next = first;
    *stack = last;
}


void	ft_rra(t_node **a)
{
	printf(ROTATE_RRA);
	ft_reverse_rotate(a);
}

void	ft_rrb(t_node **b)
{
	printf(ROTATE_RRB);
	ft_reverse_rotate(b);
}

void	ft_rrr(t_node **a, t_node **b)
{
	printf(ROTATE_RRR);
	ft_reverse_rotate(a);
	ft_reverse_rotate(b);
}
