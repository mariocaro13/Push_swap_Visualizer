/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:09:05 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/02/14 02:19:02 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movements.h"

void ft_push(t_node **src, t_node **dest) {
    if (*src == NULL) return;

    t_node *node = *src;
    *src = node->next;

    node->next = *dest;
    *dest = node;
}

void    ft_pa(t_node **a, t_node **b)
{
    printf(PUSH_PA);
    ft_push(b, a);
}

void    ft_pb(t_node **a, t_node **b)
{
    printf(PUSH_PB);
    ft_push(a, b);
}

