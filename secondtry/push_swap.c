/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:33:42 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 21:33:42 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_sorted_stack(t_stack *stack)
{
    t_stack	*tmp;

    tmp = stack;
    while (tmp)
    {
        ft_putnbr(tmp->value);
        if (tmp->next)
            write(1, " ", 1);
        tmp = tmp->next;
    }
    write(1, "\n", 1);
}

static void	index_stack(t_stack **stack)
{
    t_stack	*ptr;
    t_stack	*tmp;
    int		min;
    int		index;

    index = 1;
    while (index <= stack_size(*stack))
    {
        ptr = *stack;
        min = INT_MAX;
        while (ptr)
        {
            if (ptr->value < min && ptr->index == 0)
                min = ptr->value;
            ptr = ptr->next;
        }
        tmp = *stack;
        while (tmp)
        {
            if (tmp->value == min && tmp->index == 0)
            {
                tmp->index = index;
                break ;
            }
            tmp = tmp->next;
        }
        index++;
    }
}

static int	check_number(char *str)
{
    int	i;

    i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

static void	parse_args(int argc, char **argv, t_stack **stack)
{
    int		i;
    long	num;

    if (argc < 2)
        exit(0);
    i = 1;
    while (i < argc)
    {
        if (!check_number(argv[i]))
        {
            if (*stack)
                stack_clear(stack);
            ft_error();
        }
        num = ft_atoi(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
        {
            if (*stack)
                stack_clear(stack);
            ft_error();
        }
        stack_add_back(stack, stack_new((int)num));
        i++;
    }
    if (has_duplicates(*stack))
    {
        stack_clear(stack);
        ft_error();
    }
    index_stack(stack);
}

int	main(int argc, char **argv)
{
    t_stack	*a;
    t_stack	*b;

    a = NULL;
    b = NULL;
    parse_args(argc, argv, &a);
    if (!is_sorted(a))
    {
        if (stack_size(a) == 2)
            sa(&a, 1);
        else if (stack_size(a) == 3)
            sort_three(&a);
        else
            sort_stack(&a, &b);
    }
    print_sorted_stack(a);
    stack_clear(&a);
    stack_clear(&b);
    return (0);
}