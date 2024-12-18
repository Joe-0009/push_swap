/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <youremail@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:11:32 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 13:11:32 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_index(t_stack *stack, int value)
{
    int		*array;
    int		size;
    int		i;
    int		index;

    array = stack_to_array(stack);
    size = stack_size(stack);
    i = 0;
    index = 0;
    sort_array(array, size);
    while (i < size)
    {
        if (array[i] == value)
        {
            index = i;
            break ;
        }
        i++;
    }
    free(array);
    return (index);
}

static void	normalize_stack(t_stack **stack)
{
    t_stack	*temp;
    t_stack	*new_stack;
    int		index;

    temp = *stack;
    new_stack = NULL;
    while (temp)
    {
        index = get_index(*stack, temp->value);
        stack_add_back(&new_stack, stack_new(index));
        temp = temp->next;
    }
    stack_clear(stack);
    *stack = new_stack;
}

int	is_sorted(t_stack *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}

void	sort_three(t_stack **a)
{
    int	first;
    int	second;
    int	third;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;
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

int	find_min_position(t_stack *stack)
{
    int		min;
    int		pos;
    int		min_pos;
    t_stack	*temp;

    min = stack->value;
    pos = 0;
    min_pos = 0;
    temp = stack;
    while (temp)
    {
        if (temp->value < min)
        {
            min = temp->value;
            min_pos = pos;
        }
        pos++;
        temp = temp->next;
    }
    return (min_pos);
}

void	sort_five(t_stack **a, t_stack **b)
{
    int	min_pos;
    int	size;

    while (stack_size(*a) > 3)
    {
        min_pos = find_min_position(*a);
        size = stack_size(*a);
        if (min_pos <= size / 2)
            while (min_pos--)
                ra(a);
        else
            while (min_pos++ < size)
                rra(a);
        pb(a, b);
    }
    sort_three(a);
    while (*b)
        pa(a, b);
}

int	is_chunk_empty(t_stack *stack, int min, int max)
{
    while (stack)
    {
        if (stack->value >= min && stack->value < max)
            return (0);
        stack = stack->next;
    }
    return (1);
}

int	find_max_position(t_stack *stack)
{
    int		max;
    int		pos;
    int		max_pos;
    t_stack	*temp;

    max = stack->value;
    pos = 0;
    max_pos = 0;
    temp = stack;
    while (temp)
    {
        if (temp->value > max)
        {
            max = temp->value;
            max_pos = pos;
        }
        pos++;
        temp = temp->next;
    }
    return (max_pos);
}

void	sort_chunks(t_stack **a, t_stack **b, int size)
{
    int	chunk_size;
    int	min;
    int	max;

    if (size <= 100)
        chunk_size = size / 5;
    else
        chunk_size = size / 8;
    min = 0;
    max = chunk_size;
    normalize_stack(a);
    while (*a)
    {
        if ((*a)->value >= min && (*a)->value < max)
        {
            pb(a, b);
            if ((*b)->value < min + (chunk_size / 2))
                rb(b);
        }
        else
            ra(a);
        if (!*a || is_chunk_empty(*a, min, max))
        {
            min = max;
            max += chunk_size;
        }
    }
    while (*b)
    {
        max = find_max_position(*b);
        if (max <= stack_size(*b) / 2)
            while (max--)
                rb(b);
        else
            while (max++ < stack_size(*b))
                rrb(b);
        pa(a, b);
    }
}

void	sort_stack(t_stack **a, t_stack **b)
{
    int	size;

    size = stack_size(*a);
    if (is_sorted(*a))
        return ;
    if (size == 2)
    {
        if ((*a)->value > (*a)->next->value)
            sa(a);
    }
    else if (size == 3)
        sort_three(a);
    else if (size <= 5)
        sort_five(a, b);
    else
        sort_chunks(a, b, size);
}

void	print_final_state(t_stack *stack)
{
    write(2, "\nSorted stack: ", 14);
    while (stack)
    {
        ft_putnbr_fd(stack->value, 2);
        if (stack->next)
            write(2, " ", 1);
        stack = stack->next;
    }
    write(2, "\n", 1);
}

int	main(int argc, char **argv)
{
    t_stack	*a;
    t_stack	*b;
    int		i;

    a = NULL;
    b = NULL;
    if (argc < 2)
        return (0);
    i = 1;
    while (i < argc)
    {
        if (!stack_add_back(&a, stack_new(ft_atoi(argv[i]))))
        {
            stack_clear(&a);
            return (1);
        }
        i++;
    }
    if (has_duplicates(a))
    {
        stack_clear(&a);
        write(2, "Error\n", 6);
        return (1);
    }
    sort_stack(&a, &b);
    print_final_state(a);
    stack_clear(&a);
    stack_clear(&b);
    return (0);
}