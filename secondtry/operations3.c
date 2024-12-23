#include "push_swap.h"

void	rra(t_stack **a, int print)
{
    t_stack	*last;
    t_stack	*second_last;

    if (!*a || !(*a)->next)
        return ;
    last = *a;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *a;
    *a = last;
    if (print)
        write(1, "rra\n", 4);
}

void	rrb(t_stack **b, int print)
{
    t_stack	*last;
    t_stack	*second_last;

    if (!*b || !(*b)->next)
        return ;
    last = *b;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *b;
    *b = last;
    if (print)
        write(1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b)
{
    rra(a, 0);
    rrb(b, 0);
    write(1, "rrr\n", 4);
}