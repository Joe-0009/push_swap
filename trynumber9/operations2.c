/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youremail <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:32:46 by youremail         #+#    #+#             */
/*   Updated: 2024/12/18 12:32:46 by youremail        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ra(t_stack **a)
{
    t_stack *tmp;
    t_stack *last;

    if (!*a || !(*a)->next)
        return;
    tmp = *a;
    *a = (*a)->next;
    last = *a;
    while (last->next)
        last = last->next;
    last->next = tmp;
    tmp->next = NULL;
    write(1, "ra\n", 3);
}

void rb(t_stack **b)
{
    t_stack *tmp;
    t_stack *last;

    if (!*b || !(*b)->next)
        return;
    tmp = *b;
    *b = (*b)->next;
    last = *b;
    while (last->next)
        last = last->next;
    last->next = tmp;
    tmp->next = NULL;
    write(1, "rb\n", 3);
}

void rr(t_stack **a, t_stack **b)
{
    t_stack *tmp;
    t_stack *last;

    if (*a && (*a)->next)
    {
        tmp = *a;
        *a = (*a)->next;
        last = *a;
        while (last->next)
            last = last->next;
        last->next = tmp;
        tmp->next = NULL;
    }
    if (*b && (*b)->next)
    {
        tmp = *b;
        *b = (*b)->next;
        last = *b;
        while (last->next)
            last = last->next;
        last->next = tmp;
        tmp->next = NULL;
    }
    write(1, "rr\n", 3);
}