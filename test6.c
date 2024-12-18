#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_stack {
    int value;
    struct s_stack *next;
} t_stack;

// Utility Function Prototypes
void ft_putstr(char *str);
int ft_atoi(const char *str);
int ft_strlen(char *str);
void free_stack(t_stack **stack);
int stack_size(t_stack *stack);
int is_sorted(t_stack *stack);

// Operation Function Prototypes
void swap(t_stack **stack, char *op);
void push(t_stack **src, t_stack **dest, char *op);
void rotate(t_stack **stack, char *op);
void reverse_rotate(t_stack **stack, char *op);

// Sorting Function Prototypes
void sort_two(t_stack **stack);
void sort_three(t_stack **a);
void smart_push(t_stack **a, t_stack **b);
void final_rotation(t_stack **a);

// Utility Functions
void ft_putstr(char *str) {
    write(1, str, ft_strlen(str));
}

int ft_strlen(char *str) {
    int len;

    len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

int ft_atoi(const char *str) {
    long result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13)) {
        str++;
    }
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (int)(result * sign);
}

void free_stack(t_stack **stack) {
    t_stack *current;
    t_stack *next;

    current = *stack;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *stack = NULL;
}

int stack_size(t_stack *stack) {
    int size;

    size = 0;
    while (stack != NULL) {
        size++;
        stack = stack->next;
    }
    return size;
}

int is_sorted(t_stack *stack) {
    t_stack *current;

    current = stack;
    while (current != NULL && current->next != NULL) {
        if (current->value > current->next->value) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

// Stack Operations
void swap(t_stack **stack, char *op) {
    t_stack *first;
    t_stack *second;

    if (*stack == NULL || (*stack)->next == NULL) {
        return;
    }
    first = *stack;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *stack = second;
    ft_putstr(op);
}

void push(t_stack **src, t_stack **dest, char *op) {
    t_stack *temp;

    if (*src == NULL) {
        return;
    }
    temp = *src;
    *src = temp->next;
    temp->next = *dest;
    *dest = temp;
    ft_putstr(op);
}

void rotate(t_stack **stack, char *op) {
    t_stack *first;
    t_stack *last;

    if (*stack == NULL || (*stack)->next == NULL) {
        return;
    }
    first = *stack;
    last = first;
    while (last->next != NULL) {
        last = last->next;
    }
    *stack = first->next;
    first->next = NULL;
    last->next = first;
    ft_putstr(op);
}

void reverse_rotate(t_stack **stack, char *op) {
    t_stack *current;
    t_stack *previous;
    t_stack *last;

    if (*stack == NULL || (*stack)->next == NULL) {
        return;
    }
    current = *stack;
    previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    previous->next = NULL;
    current->next = *stack;
    *stack = current;
    ft_putstr(op);
}

// Sorting Functions
void sort_two(t_stack **stack) {
    if ((*stack)->value > (*stack)->next->value) {
        swap(stack, "sa\n");
    }
}

void sort_three(t_stack **a) {
    int first;
    int second;
    int third;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;

    if (first > second && second < third && first < third) {
        swap(a, "sa\n");
    }
    else if (first > second && second > third) {
        swap(a, "sa\n");
        reverse_rotate(a, "rra\n");
    }
    else if (first > second && second < third && first > third) {
        rotate(a, "ra\n");
    }
    else if (first < second && second > third && first < third) {
        swap(a, "sa\n");
        rotate(a, "ra\n");
    }
    else if (first < second && second > third && first > third) {
        reverse_rotate(a, "rra\n");
    }
}

int find_place(t_stack *stack, int value) {
    int index;
    t_stack *current;

    index = 0;
    current = stack;
    while (current != NULL) {
        if (current->value > value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return index;
}

void smart_push(t_stack **a, t_stack **b) {
    int size;
    int place;
    
    size = stack_size(*a);
    while (size > 3) {
        place = find_place(*b, (*a)->value);
        while (place > 0) {
            rotate(b, "rb\n");
            place--;
        }
        push(a, b, "pb\n");
        size--;
    }
    
    sort_three(a);
}

void final_rotation(t_stack **a) {
    int size;
    int half;

    size = stack_size(*a);
    half = size / 2;
    while (!is_sorted(*a)) {
        rotate(a, "ra\n");
    }
}

t_stack *create_node(int value) {
    t_stack *node;

    node = malloc(sizeof(t_stack));
    node->value = value;
    node->next = NULL;
    return node;
}

int main(int argc, char *argv[]) {
    t_stack *a;
    t_stack *b;
    int i;
    long num;

    a = NULL;
    b = NULL;
    
    if (argc < 2) {
        ft_putstr("Usage: ./push_swap <numbers>\n");
        return 1;
    }
    
    i = 1;
    while (i < argc) {
        num = ft_atoi(argv[i]);
        
        if (num > INT_MAX || num < INT_MIN) {
            ft_putstr("Error\n");
            free_stack(&a);
            return 1;
        }
        
        t_stack *current = a;
        while (current != NULL) {
            if (current->value == (int)num) {
                ft_putstr("Error\n");
                free_stack(&a);
                return 1;
            }
            current = current->next;
        }
        
        t_stack *new_node = create_node((int)num);
        if (a == NULL) {
            a = new_node;
        } else {
            current = a;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
        
        i++;
    }
    
    if (!is_sorted(a)) {
        if (stack_size(a) == 2) {
            sort_two(&a);
        } else if (stack_size(a) == 3) {
            sort_three(&a);
        } else {
            smart_push(&a, &b);
            while (b != NULL) {
                push(&b, &a, "pa\n");
            }
            final_rotation(&a);
        }
    }
    
    free_stack(&a);
    free_stack(&b);
    
    return 0;
}