/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:55:11 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 15:55:11 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	abs_value(int n)
{
    if (n < 0)
        return (n * -1);
    return (n);
}

void	get_cost(t_stack **a, t_stack **b)
{
    t_stack	*tmp_a;
    t_stack	*tmp_b;
    int		size_a;
    int		size_b;

    tmp_a = *a;
    tmp_b = *b;
    size_a = stack_size(tmp_a);
    size_b = stack_size(tmp_b);
    while (tmp_b)
    {
        tmp_b->cost_b = tmp_b->pos;
        if (tmp_b->pos > size_b / 2)
            tmp_b->cost_b = -(size_b - tmp_b->pos);
        tmp_b->cost_a = tmp_b->target_pos;
        if (tmp_b->target_pos > size_a / 2)
            tmp_b->cost_a = -(size_a - tmp_b->target_pos);
        tmp_b = tmp_b->next;
    }
}

void	do_cheapest_move(t_stack **a, t_stack **b)
{
    t_stack	*tmp;
    int		cheapest;
    int		cost_a;
    int		cost_b;

    tmp = *b;
    cheapest = 2147483647;
    while (tmp)
    {
        if (abs_value(tmp->cost_a) + abs_value(tmp->cost_b) < abs_value(cheapest))
        {
            cheapest = abs_value(tmp->cost_b) + abs_value(tmp->cost_a);
            cost_a = tmp->cost_a;
            cost_b = tmp->cost_b;
        }
        tmp = tmp->next;
    }
    do_move(a, b, cost_a, cost_b);
}

static void	do_rotate_both(t_stack **a, t_stack **b, int *cost_a, int *cost_b)
{
    while (*cost_a > 0 && *cost_b > 0)
    {
        rr(a, b);
        (*cost_a)--;
        (*cost_b)--;
    }
}

void	do_move(t_stack **a, t_stack **b, int cost_a, int cost_b)
{
    if (cost_a < 0 && cost_b < 0)
    {
        while (cost_a < 0 && cost_b < 0)
        {
            rrr(a, b);
            cost_a++;
            cost_b++;
        }
    }
    else if (cost_a > 0 && cost_b > 0)
        do_rotate_both(a, b, &cost_a, &cost_b);
    while (cost_b < 0)
    {
        rrb(b, 1);
        cost_b++;
    }
    while (cost_b > 0)
    {
        rb(b, 1);
        cost_b--;
    }
    while (cost_a < 0)
    {
        rra(a, 1);
        cost_a++;
    }
    while (cost_a > 0)
    {
        ra(a, 1);
        cost_a--;
    }
    pa(a, b);
}