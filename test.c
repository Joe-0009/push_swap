#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_stack {
    int value;
    struct s_stack *next;
} t_stack;

// Operation function prototypes
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

// Utility function prototypes
t_stack *create_node(int value);
void free_stack(t_stack *stack);
int stack_size(t_stack *stack);
int is_sorted(t_stack *stack);
void print_stack(t_stack *stack);

// Complex sorting function prototypes
void sort_three(t_stack **a);
void sort_small(t_stack **a, t_stack **b);
void turk_sort(t_stack **a, t_stack **b);
int find_optimal_location(t_stack *b, int value);
int calculate_rotations(t_stack *stack, int value);
int calculate_moves(t_stack *a, t_stack *b, int b_value);
void rotate_both(t_stack **a, t_stack **b, int *ra_count, int *rb_count);
void reverse_rotate_both(t_stack **a, t_stack **b, int *rra_count, int *rrb_count);

// Operation Implementations
void sa(t_stack **a) {
    if (!*a || !(*a)->next) return;
    t_stack *temp = *a;
    *a = (*a)->next;
    temp->next = (*a)->next;
    (*a)->next = temp;
    write(1, "sa\n", 3);
}

void sb(t_stack **b) {
    if (!*b || !(*b)->next) return;
    t_stack *temp = *b;
    *b = (*b)->next;
    temp->next = (*b)->next;
    (*b)->next = temp;
    write(1, "sb\n", 3);
}

void pa(t_stack **a, t_stack **b) {
    if (!*b) return;
    t_stack *temp = *b;
    *b = (*b)->next;
    temp->next = *a;
    *a = temp;
    write(1, "pa\n", 3);
}

void pb(t_stack **a, t_stack **b) {
    if (!*a) return;
    t_stack *temp = *a;
    *a = (*a)->next;
    temp->next = *b;
    *b = temp;
    write(1, "pb\n", 3);
}

void ra(t_stack **a) {
    if (!*a || !(*a)->next) return;
    t_stack *first = *a;
    t_stack *last = *a;
    while (last->next) last = last->next;
    *a = first->next;
    last->next = first;
    first->next = NULL;
    write(1, "ra\n", 3);
}

void rb(t_stack **b) {
    if (!*b || !(*b)->next) return;
    t_stack *first = *b;
    t_stack *last = *b;
    while (last->next) last = last->next;
    *b = first->next;
    last->next = first;
    first->next = NULL;
    write(1, "rb\n", 3);
}

void rra(t_stack **a) {
    if (!*a || !(*a)->next) return;
    t_stack *last = *a;
    t_stack *second_last = NULL;
    while (last->next) {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *a;
    *a = last;
    write(1, "rra\n", 4);
}

void rrb(t_stack **b) {
    if (!*b || !(*b)->next) return;
    t_stack *last = *b;
    t_stack *second_last = NULL;
    while (last->next) {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = *b;
    *b = last;
    write(1, "rrb\n", 4);
}

// Utility Functions
t_stack *create_node(int value) {
    t_stack *new_node = malloc(sizeof(t_stack));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_stack(t_stack *stack) {
    t_stack *temp;
    while (stack) {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}

int stack_size(t_stack *stack) {
    int size = 0;
    while (stack) {
        size++;
        stack = stack->next;
    }
    return size;
}

int is_sorted(t_stack *stack) {
    while (stack && stack->next) {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

// Find the value's ideal location in stack b
int find_optimal_location(t_stack *b, int value) {
    t_stack *current = b;
    int best_index = 0;
    int min_diff = INT_MAX;
    int index = 0;

    if (!b) return 0;

    while (current) {
        int diff = current->value - value;
        if (diff > 0 && diff < min_diff) {
            min_diff = diff;
            best_index = index;
        }
        current = current->next;
        index++;
    }

    return best_index;
}

// Calculate rotations needed to bring a value to top of stack
int calculate_rotations(t_stack *stack, int value) {
    int size = stack_size(stack);
    int index = 0;
    while (stack) {
        if (stack->value == value) {
            return index <= size / 2 ? index : index - size;
        }
        stack = stack->next;
        index++;
    }
    return 0;
}

// Calculate total moves to insert a value
int calculate_moves(t_stack *a, t_stack *b, int b_value) {
    int optimal_pos = find_optimal_location(a, b_value);
    int b_rotation = calculate_rotations(b, b_value);
    int a_rotation = (optimal_pos <= stack_size(a) / 2) ? 
                     optimal_pos : optimal_pos - stack_size(a);

    return abs(b_rotation) + abs(a_rotation);
}

// Sort three elements
void sort_three(t_stack **a) {
    int first = (*a)->value;
    int second = (*a)->next->value;
    int third = (*a)->next->next->value;

    if (first > second && second < third && first < third) 
        sa(a);
    else if (first > second && second > third)
        { sa(a); rra(a); }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
        { sa(a); ra(a); }
    else if (first < second && second > third && first > third)
        rra(a);
}

// Turk Sort for larger stacks
void turk_sort(t_stack **a, t_stack **b) {
    // Push first two elements to B
    pb(a, b);
    pb(a, b);

    // Sort remaining in A
    while (stack_size(*a) > 3) {
        int best_value = (*a)->value;
        int min_moves = INT_MAX;

        // Find element with minimal total moves
        t_stack *current = *a;
        while (current) {
            int moves = calculate_moves(*b, *a, current->value);
            if (moves < min_moves) {
                min_moves = moves;
                best_value = current->value;
            }
            current = current->next;
        }

        // Rotate best value to top and push to B
        while ((*a)->value != best_value)
            ra(a);
        pb(a, b);
    }

    // Sort final 3 in A
    sort_three(a);

    // Smart pushback from B to A
    while (*b) {
        int optimal_index = find_optimal_location(*a, (*b)->value);
        
        // Rotate to correct position
        while (optimal_index > 0) {
            ra(a);
            optimal_index--;
        }

        pa(a, b);
    }

    // Final alignment
    while (!is_sorted(*a)) {
        ra(a);
    }
}

int main(int argc, char *argv[]) {
    t_stack *a = NULL;
    t_stack *b = NULL;
    
    if (argc < 2) {
        write(2, "Usage: ./push_swap <numbers>\n", 29);
        return 1;
    }
    
    // Parse input
    for (int i = 1; i < argc; i++) {
        long num = atoi(argv[i]);
        
        // Overflow and duplicate checks
        if (num > INT_MAX || num < INT_MIN) {
            write(2, "Error\n", 6);
            free_stack(a);
            return 1;
        }
        
        t_stack *current = a;
        while (current) {
            if (current->value == (int)num) {
                write(2, "Error\n", 6);
                free_stack(a);
                return 1;
            }
            current = current->next;
        }
        
        t_stack *new_node = create_node((int)num);
        if (!a) 
            a = new_node;
        else {
            t_stack *last = a;
            while (last->next) 
                last = last->next;
            last->next = new_node;
        }
    }
    
    // Choose sorting strategy
    int size = stack_size(a);
    if (size <= 3) 
        sort_three(&a);
    else
        turk_sort(&a, &b);
    
    // Cleanup
    free_stack(a);
    free_stack(b);
    
    return 0;
}