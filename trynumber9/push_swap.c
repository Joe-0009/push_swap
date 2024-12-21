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

static void set_index(t_stack **stack, int value, int index)
{
    t_stack *tmp;

    tmp = *stack;
    while (tmp)
    {
        if (tmp->value == value)
        {
            tmp->index = index;
            return ;
        }
        tmp = tmp->next;
    }
}

static void	normalize_stack(t_stack **stack)
{
    t_stack	*temp;
    int		index;

    temp = *stack;
    while (temp)
    {
        index = get_index(*stack, temp->value);
        set_index(stack, temp->value, index);
        temp = temp->next;
    }
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
        if (stack->index >= min && stack->index < max)
            return (0);
        stack = stack->next;
    }
    return (1);
}

int	find_max_position(t_stack *stack)
{
    int		max_index;
    int		max_pos;
    t_stack	*temp;

    if(!stack)
        return (0);
    temp = stack;
    max_index = stack->index;
    max_pos = stack->pos;
    while (temp)
    {
        if (temp->index > max_index)
        {
            max_index = temp->index;
            max_pos = temp->pos;
        }
        temp = temp->next;
    }
    return (max_pos);
}
void get_target_position(t_stack **a, t_stack **b)
{
    t_stack *tmp_a;
    t_stack *tmp_b;
    int target_pos;
    int closest_larger;

    tmp_b = *b;
    while (tmp_b)
    {
        closest_larger = INT_MAX;
        target_pos = 0;
        tmp_a = *a;
        while (tmp_a)
        {
            if (tmp_a->index > tmp_b->index && tmp_a->index < closest_larger)
            {
                closest_larger = tmp_a->index;
                target_pos = tmp_a->pos;
            }
            tmp_a = tmp_a->next;
        }
        // If no larger number found, target the smallest number in stack A
        if (closest_larger == INT_MAX)
        {
            tmp_a = *a;
            closest_larger = INT_MAX;
            while (tmp_a)
            {
                if (tmp_a->index < closest_larger)
                {
                    closest_larger = tmp_a->index;
                    target_pos = tmp_a->pos;
                }
                tmp_a = tmp_a->next;
            }
        }
        tmp_b->target_pos = target_pos;
        tmp_b = tmp_b->next;
    }
}

/*static int find_closest_in_chunk(t_stack *stack, int min, int max)
{
    t_stack *tmp;
    int closest_pos;
    int min_distance;
    int current_pos;

    tmp = stack;
    closest_pos = 0;
    min_distance = INT_MAX;
    current_pos = 0;

    while (tmp)
    {
        if (tmp->index >= min && tmp->index < max)
        {
            if (current_pos < min_distance)
            {
                min_distance = current_pos;
                closest_pos = current_pos;
            }
        }
        current_pos++;
        tmp = tmp->next;
    }
    return (closest_pos);
}

static void    rotate_optimal(t_stack **stack, int pos, int size, char stack_name)
{
    if (pos <= size / 2)
    {
        while (pos--)
        {
            if (stack_name == 'a')
                ra(stack);
            else
                rb(stack);
        }
    }
    else
    {
        while (pos++ < size)
        {
            if (stack_name == 'a')
                rra(stack);
            else
                rrb(stack);
        }
    }
}*/

void sort_chunks(t_stack **a, t_stack **b, int size)
{
    int chunk_size;
    int pushed;
    int total_chunks;
    int current_chunk;
    int min;
    int max;
    int max_pos;
    int size_b;

    if (size <= 100)
        chunk_size = size / 5;
    else
        chunk_size = size / 8;
    total_chunks = (size / chunk_size) + (size % chunk_size != 0);
    current_chunk = 0;
    pushed = 0;
    normalize_stack(a);
    
    // Phase 1: Push to B in chunks
    while (current_chunk < total_chunks && *a)
    {
        min = current_chunk * chunk_size;  
        max = (current_chunk + 1) * chunk_size; 
        while (*a && pushed < max)
        {
            update_positions(*a);
            if ((*a)->index >= min && (*a)->index < max)
            {
                pb(a, b);
                // Only rotate if number is in lower half of chunk and stack has more than 2 elements
                if ((*b)->index < min + (chunk_size / 2) && (*b)->next && (*b)->index < (*b)->next->index)
                    rb(b);
                pushed++;
            }
            else if ((*a)->pos <= (size / 2))
                ra(a);
            else
                rra(a);
        }
        current_chunk++;
    }

    // Phase 2: Push back to A
    while (*b)
    {
        update_positions(*a);
        update_positions(*b);
        max_pos = find_max_position(*b);
        size_b = stack_size(*b);

        // Find next largest number position
        int next_max_pos = -1;
        int next_max_index = -1;
        t_stack *temp = *b;
        int pos = 0;
        
        while (temp)
        {
            if (temp->index > next_max_index && temp->index < (*b)->index)
            {
                next_max_index = temp->index;
                next_max_pos = pos;
            }
            pos++;
            temp = temp->next;
        }

        // Optimize rotation based on both current max and next max
        if (max_pos <= size_b / 2)
        {
            if (next_max_pos != -1 && next_max_pos <= size_b / 2 && 
                next_max_pos < max_pos)
            {
                // Rotate to next max first if it's more efficient
                while (next_max_pos--)
                    rb(b);
                pa(a, b);
                while (max_pos-- > next_max_pos)
                    rb(b);
            }
            else
            {
                while (max_pos--)
                    rb(b);
            }
        }
        else
        {
            if (next_max_pos != -1 && next_max_pos > size_b / 2 && 
                next_max_pos > max_pos)
            {
                while (next_max_pos++ < size_b)
                    rrb(b);
                pa(a, b);
                while (max_pos++ < next_max_pos)
                    rrb(b);
            }
            else
            {
                while (max_pos++ < size_b)
                    rrb(b);
            }
        }
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

void	print_final_state_values(t_stack *stack)
{
    write(2, "\nSorted stack values: ", 14);
    while (stack)
    {
        ft_putnbr_fd(stack->value, 2);
        if (stack->next)
            write(2, " ", 1);
        stack = stack->next;
    }
    write(2, "\n", 1);
}

void	print_final_state_indexes(t_stack *stack)
{
    write(2, "\nSorted stack indexes: ", 14);
    while (stack)
    {
        ft_putnbr_fd(stack->index, 2);
        if (stack->next)
            write(2, " ", 1);
        stack = stack->next;
    }
    write(2, "\n", 1);
}
void update_positions(t_stack *stack)
{
    int i;
    t_stack *tmp;
    i = 0;
    tmp = stack;
    while (tmp)
    {
        tmp->pos = i;
        i++;
        tmp = tmp->next;
    }
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
    print_final_state_values(a);

    //print_final_state_indexes(a);
    stack_clear(&a);
    stack_clear(&b);
    return (0);
}