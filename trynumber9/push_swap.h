/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youremail <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:32:46 by youremail         #+#    #+#             */
/*   Updated: 2024/12/18 12:32:46 by youremail        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
    int             value;
    struct s_stack  *next;
}   t_stack;

/* Stack Operations */
t_stack     *stack_new(int value);
int         stack_add_back(t_stack **stack, t_stack *new);
void        stack_clear(t_stack **stack);
int         stack_size(t_stack *stack);
int         *stack_to_array(t_stack *stack);

/* Operations */
void        sa(t_stack **a);
void        sb(t_stack **b);
void        ss(t_stack **a, t_stack **b);
void        pa(t_stack **a, t_stack **b);
void        pb(t_stack **a, t_stack **b);
void        ra(t_stack **a);
void        rb(t_stack **b);
void        rr(t_stack **a, t_stack **b);
void        rra(t_stack **a);
void        rrb(t_stack **b);
void        rrr(t_stack **a, t_stack **b);

/* Utils */
int         ft_atoi(const char *str);
void        sort_array(int *arr, int size);
int         get_max(t_stack *stack);
int         has_duplicates(t_stack *stack);
void        sort_stack(t_stack **a, t_stack **b);

void	print_final_state(t_stack *stack);
void	ft_putnbr_fd(int n, int fd);
int	is_sorted(t_stack *stack);
#endif