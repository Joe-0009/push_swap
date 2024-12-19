/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:21:06 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 21:21:06 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_all_save_three(t_stack **a, t_stack **b)
{
    int	size;
    int	pushed;
    int	i;

    size = stack_size(*a);
    pushed = 0;
    i = 0;
    while (size > 6 && i < size && pushed < size / 2)
    {
        if ((*a)->index <= size / 2)
        {
            pb(a, b);
            pushed++;
        }
        else
            ra(a, 1);
        i++;
    }
    while (size - pushed > 3)
    {
        pb(a, b);
        pushed++;
    }
}

void	sort_three(t_stack **stack)
{
    int	highest;

    if (!*stack || !(*stack)->next || !(*stack)->next->next)
        return ;
    highest = get_highest_index(*stack);
    if ((*stack)->index == highest)
        ra(stack, 1);
    else if ((*stack)->next->index == highest)
        rra(stack, 1);
    if ((*stack)->index > (*stack)->next->index)
        sa(stack, 1);
}

static void	shift_stack(t_stack **stack_a)
{
    int	lowest_pos;
    int	size;

    size = stack_size(*stack_a);
    lowest_pos = get_lowest_position(stack_a);
    if (lowest_pos > size / 2)
    {
        while (lowest_pos < size)
        {
            rra(stack_a, 1);
            lowest_pos++;
        }
    }
    else
    {
        while (lowest_pos > 0)
        {
            ra(stack_a, 1);
            lowest_pos--;
        }
    }
}

void	sort_stack(t_stack **a, t_stack **b)
{
    push_all_save_three(a, b);
    sort_three(a);
    while (*b)
    {
        get_target_position(a, b);
        get_cost(a, b);
        do_cheapest_move(a, b);
    }
    if (!is_sorted(*a))
        shift_stack(a);
}