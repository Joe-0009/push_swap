#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
// Reduce the number of chunks to 5
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h> // Include the necessary header for strlen

typedef struct s_stack
{
    int value;
    struct s_stack *next;
} t_stack;

// Function prototypes for stack operations
void sa(t_stack **a);
void sb(t_stack **b);
void ss(t_stack **a, t_stack **b);
void pa(t_stack **a, t_stack **b);
void pb(t_stack **a, t_stack **b);
void ra(t_stack **a);
void rb(t_stack **b);
void rr(t_stack **a, t_stack **b);
void rra(t_stack **a);
void rrb(t_stack **b);
void rrr(t_stack **a, t_stack **b);

// Utility functions
int is_sorted(t_stack *stack);
void error_exit(const char *msg);
t_stack *create_node(int value);
void free_stack(t_stack **stack);
int stack_size(t_stack *stack);
void print_stack(t_stack *stack, const char *label);

// Function prototypes for the missing functions
int find_min(t_stack *stack);
int get_position(t_stack *stack, int value);
int *create_chunks(t_stack *stack, int chunk_size, int chunk_count);
void push_chunk_to_b(t_stack **a, t_stack **b, int min, int max);
int find_max(t_stack *stack);
int *stack_to_array(t_stack *stack);
void sort_array(int *array, int size);
int find_hold_first(t_stack *stack, int min, int max);
int find_hold_second(t_stack *stack, int min, int max);
int has_values_in_range(t_stack *stack, int min, int max);
void rotate_to_top(t_stack **a, int value);
int has_numbers_below(t_stack *stack, int value);
int get_next_small(t_stack *stack, int value);
int find_closest_in_range(t_stack *stack, int min_val, int max_val);
int has_numbers_in_range(t_stack *stack, int min_val, int max_val);
// Sorting functions
void sort_three(t_stack **a);
void sort_five(t_stack **a, t_stack **b);
void chunk_sort(t_stack **a, t_stack **b);
#endif // PUSH_SWAP_H

void sa(t_stack **a)
{
    t_stack *first;
    t_stack *second;

    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *a = second;
    write(1, "sa\n", 3);
}

void sb(t_stack **b)
{
    t_stack *first;
    t_stack *second;

    if (!b || !*b || !(*b)->next)
        return;
    first = *b;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *b = second;
    write(1, "sb\n", 3);
}

void ss(t_stack **a, t_stack **b)
{
    sa(a);
    sb(b);
    write(1, "ss\n", 3);
}

void pa(t_stack **a, t_stack **b)
{
    t_stack *temp;

    if (!b || !*b)
        return;
    temp = *b;
    *b = (*b)->next;
    temp->next = *a;
    *a = temp;
    write(1, "pa\n", 3);
}

void pb(t_stack **a, t_stack **b)
{
    t_stack *temp;

    if (!a || !*a)
        return;
    temp = *a;
    *a = (*a)->next;
    temp->next = *b;
    *b = temp;
    write(1, "pb\n", 3);
}

void ra(t_stack **a)
{
    t_stack *first;
    t_stack *last;

    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    last = *a;
    while (last->next)
        last = last->next;
    *a = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "ra\n", 3);
}

void rb(t_stack **b)
{
    t_stack *first;
    t_stack *last;

    if (!b || !*b || !(*b)->next)
        return;
    first = *b;
    last = *b;
    while (last->next)
        last = last->next;
    *b = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "rb\n", 3);
}

void rr(t_stack **a, t_stack **b)
{
    ra(a);
    rb(b);
    write(1, "rr\n", 3);
}

void rra(t_stack **a)
{
    t_stack *last;
    t_stack *second_last;

    if (!a || !*a || !(*a)->next)
        return;
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
    write(1, "rra\n", 4);
}

void rrb(t_stack **b)
{
    t_stack *last;
    t_stack *second_last;

    if (!b || !*b || !(*b)->next)
        return;
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
    write(1, "rrb\n", 4);
}

void rrr(t_stack **a, t_stack **b)
{
    rra(a);
    rrb(b);
    write(1, "rrr\n", 4);
}

t_stack *create_node(int value)
{
    t_stack *node;

    node = malloc(sizeof(t_stack));
    if (!node)
        return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

void free_stack(t_stack **stack)
{
    t_stack *current;
    t_stack *next;

    current = *stack;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *stack = NULL;
}

int stack_size(t_stack *stack)
{
    int size;

    size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return size;
}

int is_sorted(t_stack *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

void error_exit(const char *msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

void print_stack(t_stack *stack, const char *label)
{
    printf("%s Stack: ", label);
    while (stack)
    {
        printf("%d ", stack->value);
        stack = stack->next;
    }
    printf("\n");
}

void sort_three(t_stack **a)
{
    int first;
    int second;
    int third;

    if (is_sorted(*a))
        return;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third && first > third)
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

void sort_five(t_stack **a, t_stack **b)
{
    int min;

    while (stack_size(*a) > 3)
    {
        min = find_min(*a);
        while ((*a)->value != min)
        {
            if (get_position(*a, min) <= stack_size(*a) / 2)
                ra(a);
            else
                rra(a);
        }
        pb(a, b);
    }
    sort_three(a);
    while (*b)
        pa(a, b);
}

int get_position(t_stack *stack, int value)
{
    int pos;

    pos = 0;
    while (stack)
    {
        if (stack->value == value)
            break;
        pos++;
        stack = stack->next;
    }
    return pos;
}
int find_optimal_position_b(t_stack *b, int value)
{
    t_stack *current;
    int pos;
    int max;
    int min;

    if (!b)
        return 0;
    max = find_max(b);
    min = find_min(b);
    pos = 0;
    current = b;
    if (value > max || value < min)
        return get_position(b, max);
    while (current->next)
    {
        if (value > current->value && value < current->next->value)
            return pos + 1;
        pos++;
        current = current->next;
    }
    return pos;
}

void chunk_sort(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    int *sorted = stack_to_array(*a);
    sort_array(sorted, size);
    int chunk_size = size / 4;

    // Push to B in 4 chunks
    for (int i = 0; i < 4; i++)
    {
        int min = i * chunk_size;
        int max = (i == 3) ? size - 1 : (i + 1) * chunk_size - 1;

        while (has_numbers_in_range(*a, sorted[min], sorted[max]))
        {
            if ((*a)->value >= sorted[min] && (*a)->value <= sorted[max])
            {
                pb(a, b);
                // Only rotate B for the first two chunks to keep smallest numbers at bottom
                if (i < 2 && *b && (*b)->next && (*b)->value < (*b)->next->value)
                    rb(b);
            }
            else
            {
                // Choose rotation direction based on closest target number
                int target_pos = find_closest_in_range(*a, sorted[min], sorted[max]);
                if (target_pos <= stack_size(*a) / 2)
                    ra(a);
                else
                    rra(a);
            }
        }
    }

    // Push back to A in descending order
    while (*b)
    {
        int max = find_max(*b);
        int pos = get_position(*b, max);
        int size_b = stack_size(*b);
        
        if (pos <= size_b / 2)
        {
            while ((*b)->value != max)
                rb(b);
        }
        else
        {
            while ((*b)->value != max)
                rrb(b);
        }
        pa(a, b);
    }
    free(sorted);
}

// Helper function to find closest number in range
int find_closest_in_range(t_stack *stack, int min_val, int max_val)
{
    int pos = 0;
    int min_pos = INT_MAX;
    int size = stack_size(stack);
    t_stack *tmp = stack;

    while (tmp)
    {
        if (tmp->value >= min_val && tmp->value <= max_val)
        {
            int curr_pos = (pos <= size / 2) ? pos : size - pos;
            if (curr_pos < min_pos)
                min_pos = pos;
        }
        pos++;
        tmp = tmp->next;
    }
    return min_pos;
}

// Helper function to check if numbers exist in range
int has_numbers_in_range(t_stack *stack, int min_val, int max_val)
{
    while (stack)
    {
        if (stack->value >= min_val && stack->value <= max_val)
            return 1;
        stack = stack->next;
    }
    return 0;
}

// Helper function to get position of next small number
int get_next_small(t_stack *stack, int value)
{
    int pos = 0;
    t_stack *tmp = stack;
    
    while (tmp)
    {
        if (tmp->value <= value)
            return pos;
        pos++;
        tmp = tmp->next;
    }
    return pos;
}

// Helper function to check if there are numbers below a certain value
int has_numbers_below(t_stack *stack, int value)
{
    while (stack)
    {
        if (stack->value <= value)
            return 1;
        stack = stack->next;
    }
    return 0;
}

void push_chunk_to_b(t_stack **a, t_stack **b, int min, int max)
{
    int pos_first, pos_second;
    int size;
    t_stack *temp;

    while (has_values_in_range(*a, min, max))
    {
        pos_first = -1;
        pos_second = -1;
        size = stack_size(*a);
        temp = *a;

        // Find two closest numbers in range from both ends
        for (int i = 0; i < size; i++)
        {
            if (temp->value >= min && temp->value <= max)
            {
                if (pos_first == -1)
                    pos_first = i;
                else
                {
                    pos_second = i;
                    break;
                }
            }
            temp = temp->next;
        }

        // Choose the most efficient rotation
        if (pos_first != -1 && (pos_second == -1 || pos_first <= size - pos_second))
        {
            if (pos_first <= size / 2)
            {
                while (pos_first--)
                    ra(a);
            }
            else
            {
                while (pos_first++ < size)
                    rra(a);
            }
        }
        else if (pos_second != -1)
        {
            if (pos_second <= size / 2)
            {
                while (pos_second--)
                    ra(a);
            }
            else
            {
                while (pos_second++ < size)
                    rra(a);
            }
        }
        pb(a, b);
    }
}
void rotate_to_top(t_stack **stack, int value)
{
    int pos = get_position(*stack, value);
    int size = stack_size(*stack);

    if (pos <= size / 2)
    {
        while ((*stack)->value != value)
            ra(stack);
    } else
    {
        while ((*stack)->value != value)
            rra(stack);
    }
}

void rotate_closer_to_top(t_stack **a, int hold_first, int hold_second) {
    int pos_first;
    int pos_second;
    int size;

    pos_first = get_position(*a, hold_first);
    pos_second = get_position(*a, hold_second);
    size = stack_size(*a);
    if (pos_first <= size / 2 && pos_second <= size / 2)
    {
        if (pos_first <= pos_second)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    } else if (pos_first > size / 2 && pos_second > size / 2)
    {
        if (pos_first >= pos_second)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    } else
    {
        if (pos_first <= size / 2)
            rotate_to_top(a, hold_first);
        else
            rotate_to_top(a, hold_second);
    }
}

void rotate_both_stacks(t_stack **a, t_stack **b, int target_a, int target_b)
{
    int size_a = stack_size(*a);
    int size_b = stack_size(*b);
    int pos_a = get_position(*a, target_a);
    int pos_b = target_b;

    // Both need rotation up
    while (pos_a > 0 && pos_b > 0 && pos_a <= size_a / 2 && pos_b <= size_b / 2)
    {
        rr(a, b);
        pos_a--;
        pos_b--;
    }
    // Both need rotation down
    while (pos_a > size_a / 2 && pos_b > size_b / 2 && pos_a < size_a && pos_b < size_b)
    {
        rrr(a, b);
        pos_a = (pos_a + 1) % size_a;
        pos_b = (pos_b + 1) % size_b;
    }
    // Complete remaining rotations individually
    while ((*a)->value != target_a)
    {
        if (pos_a <= size_a / 2)
            ra(a);
        else
            rra(a);
    }
    while (pos_b > 0)
    {
        if (pos_b <= size_b / 2)
            rb(b);
        else
            rrb(b);
        pos_b--;
    }
}




int find_hold_first(t_stack *stack, int min, int max)
{
    int pos;

    pos = 0;
    while (stack)
    {
        if (stack->value >= min && stack->value <= max)
            return stack->value;
        stack = stack->next;
        pos++;
    }
    return -1;
}

int find_hold_second(t_stack *stack, int min, int max)
{
    int pos;
    t_stack *current;

    pos = stack_size(stack) - 1;
    current = stack;
    while (current)
    {
        if (current->value >= min && current->value <= max)
            return current->value;
        current = current->next;
        pos--;
    }
    return -1;
}

int has_values_in_range(t_stack *stack, int min, int max)
{
    while (stack)
    {
        if (stack->value >= min && stack->value <= max)
            return 1;
        stack = stack->next;
    }
    return 0;
}

int find_min(t_stack *stack)
{
    int min;

    min = stack->value;
    while (stack)
    {
        if (stack->value < min)
            min = stack->value;
        stack = stack->next;
    }
    return min;
}

int find_max(t_stack *stack)
{
    int max;

    max = stack->value;
    while (stack)
    {
        if (stack->value > max)
            max = stack->value;
        stack = stack->next;
    }
    return max;
}

int *create_chunks(t_stack *stack, int chunk_size, int chunk_count)
{
    int *chunks;
    int *values;
    int i;

    chunks = malloc(sizeof(int) * (chunk_count + 1));
    values = stack_to_array(stack);
    sort_array(values, stack_size(stack));

    i = 0;
    while (i < chunk_count)
    {
        chunks[i] = values[i * chunk_size];
        i++;
    }
    chunks[chunk_count] = values[stack_size(stack) - 1];

    free(values);
    return chunks;
}

int *stack_to_array(t_stack *stack)
{
    int size;
    int *array;
    int i;

    size = stack_size(stack);
    array = malloc(sizeof(int) * size);
    i = 0;
    while (i < size)
    {
        array[i] = stack->value;
        stack = stack->next;
        i++;
    }
    return array;
}

void sort_array(int *array, int size)
{
    int i;
    int j;
    int temp;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    t_stack *a;
    t_stack *b;
    int i;
    long num;
    t_stack *new_node;
    t_stack *last;
    int size;

    a = NULL;
    b = NULL;

    if (argc < 2)
    {
        write(2, "Usage: ./push_swap <numbers>\n", 29);
        return 1;
    }

    i = 1;
    while (i < argc)
    {
        num = atol(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
        {
            write(2, "Error\n", 6);
            free_stack(&a);
            return 1;
        }
        new_node = create_node((int)num);
        if (!a)
            a = new_node;
        else
        {
            last = a;
            while (last->next)
                last = last->next;
            last->next = new_node;
        }
        i++;
    }

    if (is_sorted(a))
    {
        print_stack(a, "Sorted");
        free_stack(&a);
        return 0;
    }

    size = stack_size(a);
    if (size <= 3)
        sort_three(&a);
    else if (size <= 5)
        sort_five(&a, &b);
    else
        chunk_sort(&a, &b);
    print_stack(a, "Sorted");
    free_stack(&a);
    free_stack(&b);
    return 0;
}
