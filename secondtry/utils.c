/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:55:11 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 15:55:11 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

long	ft_atoi(const char *str)
{
    long	result;
    int		sign;
    int		i;

    result = 0;
    sign = 1;
    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX && sign == 1)
            ft_error();
        if (result > ((long)INT_MAX + 1) && sign == -1)
            ft_error();
        i++;
    }
    return (sign * result);
}

int	is_sorted(t_stack *stack)
{
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}



int	has_duplicates(t_stack *stack)
{
    t_stack	*tmp;

    while (stack)
    {
        tmp = stack->next;
        while (tmp)
        {
            if (stack->value == tmp->value)
                return (1);
            tmp = tmp->next;
        }
        stack = stack->next;
    }
    return (0);
}

void	ft_putnbr(int n)
{
    char	c;

    if (n == -2147483648)
    {
        write(1, "-2147483648", 11);
        return ;
    }
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    c = '0' + (n % 10);
    write(1, &c, 1);
}