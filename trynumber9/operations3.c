/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youremail <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:32:46 by youremail         #+#    #+#             */
/*   Updated: 2024/12/18 12:32:46 by youremail        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rra(t_stack **a)
{
    t_stack *tmp;
    t_stack *last;

    if (!*a || !(*a)->next)
        return;
    tmp = *a;
    while (tmp->next->next)
        tmp = tmp->next;
    last = tmp->next;
    tmp->next = NULL;
    last->next = *a;
    *a = last;
    write(1, "rra\n", 4);
}

void rrb(t_stack **b)
{
    t_stack *tmp;
    t_stack *last;

    if (!*b || !(*b)->next)
        return;
    tmp = *b;
    while (tmp->next->next)
        tmp = tmp->next;
    last = tmp->next;
    tmp->next = NULL;
    last->next = *b;
    *b = last;
    write(1, "rrb\n", 4);
}

void rrr(t_stack **a, t_stack **b)
{
    t_stack *tmp;
    t_stack *last;

    if (*a && (*a)->next)
    {
        tmp = *a;
        while (tmp->next->next)
            tmp = tmp->next;
        last = tmp->next;
        tmp->next = NULL;
        last->next = *a;
        *a = last;
    }
    if (*b && (*b)->next)
    {
        tmp = *b;
        while (tmp->next->next)
            tmp = tmp->next;
        last = tmp->next;
        tmp->next = NULL;
        last->next = *b;
        *b = last;
    }
    write(1, "rrr\n", 4);
}