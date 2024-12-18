/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youremail <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:32:46 by youremail         #+#    #+#             */
/*   Updated: 2024/12/18 12:32:46 by youremail        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *stack_new(int value)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->next = NULL;
    return (new);
}

int stack_add_back(t_stack **stack, t_stack *new)
{
    t_stack *last;

    if (!new)
        return (0);
    if (!*stack)
    {
        *stack = new;
        return (1);
    }
    last = *stack;
    while (last->next)
        last = last->next;
    last->next = new;
    return (1);
}

void stack_clear(t_stack **stack)
{
    t_stack *tmp;

    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
}

int stack_size(t_stack *stack)
{
    int size;

    size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return (size);
}

int *stack_to_array(t_stack *stack)
{
    int *arr;
    int size;
    int i;

    size = stack_size(stack);
    arr = (int *)malloc(sizeof(int) * size);
    if (!arr)
        return (NULL);
    i = 0;
    while (stack)
    {
        arr[i++] = stack->value;
        stack = stack->next;
    }
    return (arr);
}