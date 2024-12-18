/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youremail <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:32:46 by youremail         #+#    #+#             */
/*   Updated: 2024/12/18 12:32:46 by youremail        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sa(t_stack **a)
{
    t_stack *tmp;

    if (!*a || !(*a)->next)
        return;
    tmp = (*a)->next;
    (*a)->next = tmp->next;
    tmp->next = *a;
    *a = tmp;
    write(1, "sa\n", 3);
}

void sb(t_stack **b)
{
    t_stack *tmp;

    if (!*b || !(*b)->next)
        return;
    tmp = (*b)->next;
    (*b)->next = tmp->next;
    tmp->next = *b;
    *b = tmp;
    write(1, "sb\n", 3);
}

void ss(t_stack **a, t_stack **b)
{
    t_stack *tmp;

    if (*a && (*a)->next)
    {
        tmp = (*a)->next;
        (*a)->next = tmp->next;
        tmp->next = *a;
        *a = tmp;
    }
    if (*b && (*b)->next)
    {
        tmp = (*b)->next;
        (*b)->next = tmp->next;
        tmp->next = *b;
        *b = tmp;
    }
    write(1, "ss\n", 3);
}

void pa(t_stack **a, t_stack **b)
{
    t_stack *tmp;

    if (!*b)
        return;
    tmp = *b;
    *b = (*b)->next;
    tmp->next = *a;
    *a = tmp;
    write(1, "pa\n", 3);
}

void pb(t_stack **a, t_stack **b)
{
    t_stack *tmp;

    if (!*a)
        return;
    tmp = *a;
    *a = (*a)->next;
    tmp->next = *b;
    *b = tmp;
    write(1, "pb\n", 3);
}