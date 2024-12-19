/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 21:27:50 by Joe-0009         #+#    #+#             */
/*   Updated: 2024-12-18 21:27:50 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_target(t_stack **a, int b_idx, int target_idx, int target_pos)
{
    t_stack	*tmp_a;

    tmp_a = *a;
    while (tmp_a)
    {
        if (tmp_a->index > b_idx && tmp_a->index < target_idx)
        {
            target_idx = tmp_a->index;
            target_pos = tmp_a->pos;
        }
        tmp_a = tmp_a->next;
    }
    if (target_idx != INT_MAX)
        return (target_pos);
    tmp_a = *a;
    while (tmp_a)
    {
        if (tmp_a->index < target_idx)
        {
            target_idx = tmp_a->index;
            target_pos = tmp_a->pos;
        }
        tmp_a = tmp_a->next;
    }
    return (target_pos);
}

void	get_position(t_stack **stack)
{
    t_stack	*tmp;
    int		i;

    tmp = *stack;
    i = 0;
    while (tmp)
    {
        tmp->pos = i;
        tmp = tmp->next;
        i++;
    }
}

void	get_target_position(t_stack **a, t_stack **b)
{
    t_stack	*tmp_b;
    int		target_pos;

    tmp_b = *b;
    get_position(a);
    get_position(b);
    target_pos = 0;
    while (tmp_b)
    {
        target_pos = get_target(a, tmp_b->index, INT_MAX, target_pos);
        tmp_b->target_pos = target_pos;
        tmp_b = tmp_b->next;
    }
}