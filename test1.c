#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int value;
    struct stack *n;
} s_stack;

s_stack *get_stack_bottom(s_stack *stack)
{
    while (stack && stack->n != NULL)
        stack = stack->n;
    return (stack);
}

s_stack *get_stack_before_bottom(s_stack *stack)
{
    while (stack && stack->n && stack->n->n != NULL)
        stack = stack->n;
    return (stack);
}

s_stack *ft_new_node(int value)
{
    s_stack *new_node;
    new_node = (s_stack *)malloc(sizeof(s_stack));
    if (!new_node)
        return (NULL);
    new_node->value = value;
    new_node->n = NULL;
    return (new_node);
}

void ft_add_back(s_stack **stack, s_stack *new)
{
    s_stack *head;
    if (!stack || !new)
        return;
    if (*stack == NULL)
    {
        *stack = new;
        new->n = NULL;
        return;
    }
    head = get_stack_bottom(*stack);
    head->n = new;
}

void rotate(s_stack **stack)
{
    s_stack *head;
    s_stack *tmp;
    if (!stack || !*stack)
        return;
    head = *stack;
    tmp = head->n;
    while (head->n)
        head = head->n;
    head->n = *stack;
    (*stack)->n = NULL;
    *stack = tmp;
}

void reverse_rotate(s_stack **stack)
{
    s_stack *head;
    s_stack *tmp;
    if (!stack || !*stack)
        return;
    head = get_stack_before_bottom(*stack);
    tmp = head->n;
    head->n = NULL;
    tmp->n = *stack;
    *stack = tmp;
}

void swap_first_2(s_stack **stack)
{
    s_stack *tmp;
    if (*stack && (*stack)->n)
    {
        tmp = (*stack)->n;
        (*stack)->n = tmp->n;
        tmp->n = *stack;
        *stack = tmp;
    }
}

void push(s_stack **stack1, s_stack **stack2)
{
    s_stack *head1;
    if (!stack1)
        return;
    head1 = *stack1;
    *stack1 = head1->n;
    head1->n = *stack2;
    *stack2 = head1;
}

void sort_three(s_stack **stack)
{
    int first;
    int second;
    int third;
    first = (*stack)->value;
    second = (*stack)->n->value;
    third = (*stack)->n->n->value;
    if (first < second && second > third && first < third)
        reverse_rotate(stack);
    else if (first > second && second < third && first > third)
        rotate(stack);
    else if (first > second && second > third)
        swap_first_2(stack), reverse_rotate(stack);
    else if (first > second && second < third && first < third)
        swap_first_2(stack);
    else if (first < second && second > third && first < third)
        swap_first_2(stack), rotate(stack);
}

s_stack *find_small_value(s_stack *stack)
{
    s_stack *small;
    small = stack;
    while (stack)
    {
        if (stack->value < small->value)
            small = stack;
        stack = stack->n;
    }
    return small;
}

void sort_five(s_stack **stack1, s_stack **stack2)
{
    s_stack *small;
    
    // Push two smallest elements from stack1 to stack2
    for (int i = 0; i < 2; i++) {
        small = find_small_value(*stack1);
        while ((*stack1)->value != small->value)
            rotate(stack1);
        push(stack1, stack2);
    }

    // Sort the remaining three elements in stack1
    sort_three(stack1);

    // Push the elements back from stack2 to stack1
    while (*stack2)
    {
        push(stack2, stack1);  // Push back from stack2 to stack1
    }
}

int main(int ac, char **av)
{
    s_stack *stack1 = NULL;
    s_stack *stack2 = NULL;
    s_stack *head1;
    s_stack *head2;
    int i = 1;

    if (ac < 2)
    {
        printf("Please provide numbers to sort.\n");
        return 1;
    }

    while (i < ac)
    {
        ft_add_back(&stack1, ft_new_node(atoi(av[i++])));
    }

    sort_five(&stack1, &stack2);

    head1 = stack1;
    printf("Stack 1 (sorted):\n");
    while (head1)
    {
        printf("%d\n", head1->value);
        head1 = head1->n;
    }

    printf("Stack 2 (temporary):\n");
    head2 = stack2;
    while (head2)
    {
        printf("%d\n", head2->value);
        head2 = head2->n;
    }

    return 0;
}
