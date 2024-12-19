/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:53:44 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 15:53:44 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*stack_new(int value)
{
    t_stack	*new;

    new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->index = 0;
    new->pos = -1;
    new->target_pos = -1;
    new->cost_a = -1;
    new->cost_b = -1;
    new->next = NULL;
    return (new);
}

t_stack	*stack_last(t_stack *stack)
{
    if (!stack)
        return (NULL);
    while (stack->next)
        stack = stack->next;
    return (stack);
}

void	stack_add_back(t_stack **stack, t_stack *new)
{
    t_stack	*last;

    if (!new)
        return ;
    if (!*stack)
    {
        *stack = new;
        return ;
    }
    last = stack_last(*stack);
    last->next = new;
}

int	stack_size(t_stack *stack)
{
    int	size;

    size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return (size);
}

void	stack_clear(t_stack **stack)
{
    t_stack	*tmp;

    if (!stack)
        return ;
    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
    *stack = NULL;
}