/* stack_ops.c */
#include "push_swap.h"

void sa(t_stack *a) {
    if (a->top < 1) return;
    int temp = a->array[a->top];
    a->array[a->top] = a->array[a->top - 1];
    a->array[a->top - 1] = temp;
    write(1, "sa\n", 3);
}

void sb(t_stack *b) {
    if (b->top < 1) return;
    int temp = b->array[b->top];
    b->array[b->top] = b->array[b->top - 1];
    b->array[b->top - 1] = temp;
    write(1, "sb\n", 3);
}

void ss(t_stack *a, t_stack *b) {
    sa(a);
    sb(b);
    write(1, "ss\n", 3);
}

void pa(t_stack *a, t_stack *b) {
    if (b->top == -1) return;
    a->top++;
    a->array[a->top] = b->array[b->top];
    b->top--;
    write(1, "pa\n", 3);
}

void pb(t_stack *a, t_stack *b) {
    if (a->top == -1) return;
    b->top++;
    b->array[b->top] = a->array[a->top];
    a->top--;
    write(1, "pb\n", 3);
}

void ra(t_stack *a) {
    if (a->top < 1) return;
    int temp = a->array[a->top];
    for (int i = a->top; i > 0; i--) {
        a->array[i] = a->array[i-1];
    }
    a->array[0] = temp;
    write(1, "ra\n", 3);
}

void rb(t_stack *b) {
    if (b->top < 1) return;
    int temp = b->array[b->top];
    for (int i = b->top; i > 0; i--) {
        b->array[i] = b->array[i-1];
    }
    b->array[0] = temp;
    write(1, "rb\n", 3);
}

void rr(t_stack *a, t_stack *b) {
    ra(a);
    rb(b);
    write(1, "rr\n", 3);
}

void rra(t_stack *a) {
    if (a->top < 1) return;
    int temp = a->array[0];
    for (int i = 0; i < a->top; i++) {
        a->array[i] = a->array[i+1];
    }
    a->array[a->top] = temp;
    write(1, "rra\n", 3);
}

void rrb(t_stack *b) {
    if (b->top < 1) return;
    int temp = b->array[0];
    for (int i = 0; i < b->top; i++) {
        b->array[i] = b->array[i+1];
    }
    b->array[b->top] = temp;
    write(1, "rrb\n", 3);
}

void rrr(t_stack *a, t_stack *b) {
    rra(a);
    rrb(b);
    write(1, "rrr\n", 3);
}
