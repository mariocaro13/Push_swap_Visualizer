/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:56:25 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/02/14 00:11:08 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movements.h"

void ft_rotate(t_node **stack) {
    t_node *first = *stack;
    t_node *last = *stack;

    while (last->next != NULL) last = last->next;
    *stack = first->next;
    first->next = NULL;
    last->next = first;
}

void	ft_ra(t_node **a)
{
	printf(ROTATE_RA);
	ft_rotate(a);
}

void	ft_rb(t_node **b)
{
	printf(ROTATE_RB);
	ft_rotate(b);
}

void	ft_rr(t_node **a, t_node **b)
{
	printf(ROTATE_RR);
	ft_rotate(a);
	ft_rotate(b);
}
