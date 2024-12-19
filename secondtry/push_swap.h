/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Joe-0009 <Joe-0009@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:21:06 by Joe-0009         #+#    #+#             */
/*   Updated: 2024/12/18 21:21:06 by Joe-0009        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
    int				value;
    int				index;
    int				pos;
    int				target_pos;
    int				cost_a;
    int				cost_b;
    struct s_stack	*next;
}	t_stack;

/* Stack Functions */
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new);
t_stack	*stack_last(t_stack *stack);
void	stack_clear(t_stack **stack);
int		stack_size(t_stack *stack);

/* Operations */
void	sa(t_stack **a, int print);
void	sb(t_stack **b, int print);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a, int print);
void	rb(t_stack **b, int print);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a, int print);
void	rrb(t_stack **b, int print);
void	rrr(t_stack **a, t_stack **b);

/* Position Functions */
void	get_position(t_stack **stack);
void	get_target_position(t_stack **a, t_stack **b);
void	get_cost(t_stack **a, t_stack **b);
void	do_cheapest_move(t_stack **a, t_stack **b);

/* Sort Functions */
void	sort_three(t_stack **stack);
void	sort_stack(t_stack **a, t_stack **b);
int		get_highest_index(t_stack *stack);
int		get_lowest_position(t_stack **stack);

/* Cost Functions */
void	do_move(t_stack **a, t_stack **b, int cost_a, int cost_b);

/* Utils */
long		ft_atoi(const char *str);
void	ft_error(void);
int		is_sorted(t_stack *stack);
int		has_duplicates(t_stack *stack);
void	ft_putnbr(int n);

#endif