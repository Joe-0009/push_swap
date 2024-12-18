/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <youremail@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:29:25 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 12:29:25 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int get_max_bits(t_stack *stack)
{
    int max = get_max(stack);
    int max_bits = 0;
    
    while ((max >> max_bits) != 0)
        max_bits++;
    return max_bits;
}

static int get_index(t_stack *stack, int value)
{
    int *array = stack_to_array(stack);
    int size = stack_size(stack);
    int i;
    int index = 0;
    
    sort_array(array, size);
    for (i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            index = i;
            break;
        }
    }
    free(array);
    return index;
}

static void normalize_stack(t_stack **stack)
{
    t_stack *temp = *stack;
    t_stack *new_stack = NULL;
    
    while (temp)
    {
        int index = get_index(*stack, temp->value);
        stack_add_back(&new_stack, stack_new(index));
        temp = temp->next;
    }
    stack_clear(stack);
    *stack = new_stack;
}

void radix_sort(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    int max_bits = get_max_bits(*a);
    int i, j;

    normalize_stack(a);

    for (i = 0; i < max_bits; i++)
    {
        for (j = 0; j < size; j++)
        {
            int num = (*a)->value;
            if ((num >> i) & 1)
                ra(a);
            else
                pb(a, b);
        }
        while (*b)
            pa(a, b);
    }
}

int is_sorted(t_stack *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

void sort_small(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    (void)b;
    if (size == 2)
    {
        if ((*a)->value > (*a)->next->value)
            sa(a);
    }
    else if (size == 3)
    {
        int first = (*a)->value;
        int second = (*a)->next->value;
        int third = (*a)->next->next->value;

        if (first > second && second < third && first < third)
            sa(a);
        else if (first > second && second > third)
        {
            sa(a);
            rra(a);
        }
        else if (first > second && second < third && first > third)
            ra(a);
        else if (first < second && second > third && first < third)
        {
            sa(a);
            ra(a);
        }
        else if (first < second && second > third && first > third)
            rra(a);
    }
}

void sort_stack(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);

    if (is_sorted(*a))
        return;
    if (size <= 3)
        sort_small(a, b);
    else
        radix_sort(a, b);
}

int main(int argc, char **argv)
{
    t_stack *a = NULL;
    t_stack *b = NULL;
    int i;

    if (argc < 2)
        return 0;

    // Parse arguments and build stack
    for (i = 1; i < argc; i++)
    {
        int num = ft_atoi(argv[i]);
        if (!stack_add_back(&a, stack_new(num)))
        {
            stack_clear(&a);
            return 1;
        }
    }

    // Check for duplicates
    if (has_duplicates(a))
    {
        stack_clear(&a);
        write(2, "Error\n", 6);
        return 1;
    }

    sort_stack(&a, &b);

    // Cleanup
    stack_clear(&a);
    stack_clear(&b);
    return 0;
}