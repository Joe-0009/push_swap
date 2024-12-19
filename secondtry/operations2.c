/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 15:58:32 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack **a, int print)
{
    t_stack	*tmp;

    if (!*a || !(*a)->next)
        return ;
    tmp = *a;
    *a = (*a)->next;
    tmp->next = NULL;
    stack_last(*a)->next = tmp;
    if (print)
        write(1, "ra\n", 3);
}

void	rb(t_stack **b, int print)
{
    t_stack	*tmp;

    if (!*b || !(*b)->next)
        return ;
    tmp = *b;
    *b = (*b)->next;
    tmp->next = NULL;
    stack_last(*b)->next = tmp;
    if (print)
        write(1, "rb\n", 3);
}

void	rr(t_stack **a, t_stack **b)
{
    ra(a, 0);
    rb(b, 0);
    write(1, "rr\n", 3);
}