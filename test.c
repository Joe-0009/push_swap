#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int value;
    struct stack *n;
    
} s_stack;

s_stack	*get_stack_bottom(s_stack *stack)
{
	while (stack && stack->n != NULL)
		stack = stack->n;
	return (stack);
}

s_stack	*get_stack_before_bottom(s_stack *stack)
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
        return ;
    if (*stack == NULL)
    {
        *stack = new;
        new->n = NULL;
        return ;
    }
    head = get_stack_bottom(*stack);
    
    head->n = new;
}

void rotate(s_stack **stack)
{
    s_stack *head;
    s_stack *tmp;

    if (!stack || !*stack)
        return ;
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
    s_stack *tmp;       //4 3 2 1 6 8 
                                 //^ ^ tmp
                                //head
    if (!stack || !*stack)
        return ; 
    head = get_stack_before_bottom(*stack);
    tmp = head->n;
    head->n = NULL;
    tmp->n = *stack;
    *stack = tmp;   
}

void swap_first_2(s_stack **stack)
{
    s_stack *head;
    s_stack *tmp;

    tmp = *stack;
    head = *stack;
    tmp = tmp->n;
    head->n = head->n->n;
    tmp->n = head;

    *stack = tmp;
}

void push(s_stack **stack1, s_stack **stack2)
{
    s_stack *head1;

    if (!stack1)
        return ;
    head1 = *stack1;
    *stack1 = head1->n;;
    head1->n = *stack2;  
    *stack2 = head1;
}
void rr(s_stack **stack1, s_stack **stack2)
{
    reverse_rotate(stack1);
    reverse_rotate(stack2);
}
int	get_stack_size(s_stack	*stack)
{
	int	size;

	size = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->n;
		size++;
	}
	return (size);
}
s_stack *find_small_value(s_stack *stack)
{
    s_stack *small;
    int value;

    small = stack;
    while (stack)
    {
        if (stack->value < small->value)
            small = stack;
        stack = stack->n;
    }
    return (small);
}




void sort_three(s_stack **stack)
{
    int first;
    int second;   //231 // 312 //321 //213 // 132
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
    else if(first > second && second < third && first < third)
        swap_first_2(stack);
    else if(first < second && second > third && first < third)
        swap_first_2(stack), rotate(stack);

}

void sort_five(s_stack **stack1, s_stack **stack2)
{
    s_stack *small;

    small = find_small_value(*stack1);
    while ((*stack1)-> value != small->value) 
        rotate(stack1);
    push(stack1, stack2);
    small = find_small_value(*stack1);
    while ((*stack1)-> value != small->value) 
        rotate(stack1);
    push(stack1, stack2);
    sort_three(stack1);
    push(stack2, stack1);
    push(stack2, stack1);
}

int main(int ac, char **av)
{
    s_stack *head1;
    s_stack *head2;
    s_stack *stack1 = NULL;
    s_stack *stack2 = NULL;
    int i = 1;
    
// stack 1
    while (i <= ac)
        ft_add_back(&stack1 ,ft_new_node(atoi(av[i++])));

   

    sort_five(&stack1, &stack2);
     head1 = stack1;
    while (head1)
    {
        printf("%d\n", head1->value); 
        head1 = head1->n;
    }
     printf("stack 2\n"); 

    head2 = stack2;
    while (head2)
    {
        printf("%d\n", head2->value); 
        head2 = head2->n;
    }
   
}

