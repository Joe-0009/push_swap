#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_stack {
    int value;
    struct s_stack *next;
} t_stack;

// Utility Function Prototypes
void ft_putstr(char *str);
int ft_atoi(const char *str, int *error);
int ft_strlen(char *str);
void free_stack(t_stack **stack);
int stack_size(t_stack *stack);
int is_sorted(t_stack *stack);
void print_stack(t_stack *stack);

// Operation Function Prototypes
void swap(t_stack **stack, char *op);
void push(t_stack **src, t_stack **dest, char *op);
void rotate(t_stack **stack, char *op);
void reverse_rotate(t_stack **stack, char *op);

// Sorting Function Prototypes
void quick_sort_stack(t_stack **a, t_stack **b);
int partition(t_stack **a, t_stack **b, int pivot);

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

int ft_atoi(const char *str, int *error) {
    long result;
    int sign;

    result = 0;
    sign = 1;
    *error = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13)) {
        str++;
    }

    if (*str == '+' || *str == '-') {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }

    if (*str < '0' || *str > '9') {
        *error = 1;
        return 0;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        if (result > INT_MAX) {
            *error = 1;
            return 0;
        }
        str++;
    }

    if (*str != '\0') {
        *error = 1;
        return 0;
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
    while (stack != NULL && stack->next != NULL) {
        if (stack->value > stack->next->value) {
            return 0;
        }
        stack = stack->next;
    }
    return 1;
}

void print_stack(t_stack *stack) {
    while (stack != NULL) {
        char buffer[12];
        int len = 0;
        int num = stack->value;
        int is_negative = 0;

        if (num < 0) {
            is_negative = 1;
            num = -num;
            buffer[len++] = '-';
        }

        if (num == 0) {
            buffer[len++] = '0';
        } else {
            int temp_len = 0;
            char temp[11];
            
            while (num > 0) {
                temp[temp_len++] = (num % 10) + '0';
                num /= 10;
            }
            
            while (temp_len > 0) {
                buffer[len++] = temp[--temp_len];
            }
        }
        
        buffer[len++] = ' ';
        
        write(1, buffer, len);
        
        stack = stack->next;
    }
    write(1, "\n", 1);
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

// Advanced Sorting
int get_median(t_stack *stack, int size) {
    int *arr;
    int median;
    int i;
    int j;
    t_stack *current;

    arr = malloc(size * sizeof(int));
    current = stack;
    
    i = 0;
    while (i < size)
    {
        arr[i] = current->value;
        current = current->next;
        i++;
    }

    // Simple bubble sort to find median
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    median = arr[size / 2];
    free(arr);
    return median;
}

int partition(t_stack **a, t_stack **b, int pivot) {
    int pushed = 0;
    int rotations = 0;
    int size = stack_size(*a); // Assuming you have a function to get the size of the stack

    // Move elements smaller than pivot to stack b
    while (rotations < size) {
        if ((*a)->value < pivot) {
            push(a, b, "pb\n");
            pushed++;
            size--; // Decrease size as we have removed an element from stack a
        } else {
            rotate(a, "ra\n");
            rotations++;
        }
    }

    return pushed;
}

void quick_sort_stack(t_stack **a, t_stack **b) {
    int size = stack_size(*a);
    int median;
    int pushed;

    // Base case: return if the stack has 1 or 0 elements
    if (size <= 1) {
        return;
    }

    // Step 1: If the stack size is small, do a simple sort
    if (size <= 3) {
        // Sort small stacks (2 or 3 elements) directly
        if ((*a)->value > (*a)->next->value) {
            swap(a, "sa\n");
        }
        if (size == 3 && (*a)->next->value > (*a)->next->next->value) {
            push(a, b, "pb\n");
            swap(a, "sa\n");
            push(b, a, "pa\n");
        }
        return;
    }

    // Step 2: Find the median to use as a pivot
    median = get_median(*a, size);

    // Step 3: Partition stack a into two parts, push smaller elements to b
    pushed = partition(a, b, median);

    // Step 4: Sort stack a (elements larger than pivot) and b (smaller elements)
    quick_sort_stack(a, b);  // Recursively sort larger elements in a
    quick_sort_stack(b, a);  // Recursively sort smaller elements in b

    // Step 5: Push elements back from b to a
    while (pushed > 0) {
        push(b, a, "pa\n");
        pushed--;
    }
}


t_stack *create_node(int value) {
    t_stack *node;

    node = malloc(sizeof(t_stack));
    node->value = value;
    node->next = NULL;
    return node;
}

int check_duplicates(t_stack *stack, int value) {
    while (stack != NULL) {
        if (stack->value == value) {
            return 1;
        }
        stack = stack->next;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    t_stack *a;
    t_stack *b;
    int i;
    int num;
    int error;

    a = NULL;
    b = NULL;
    
    if (argc < 2) {
        ft_putstr("Usage: ./push_swap <numbers>\n");
        return 1;
    }
    
    i = 1;
    while (i < argc) {
        num = ft_atoi(argv[i], &error);
        
        if (error) {
            ft_putstr("Error\n");
            free_stack(&a);
            return 1;
        }
        
        if (check_duplicates(a, num)) {
            ft_putstr("Error\n");
            free_stack(&a);
            return 1;
        }
        
        t_stack *new_node = create_node(num);
        if (a == NULL) {
            a = new_node;
        } else {
            t_stack *current = a;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
        
        i++;
    }
    
    if (!is_sorted(a)) {
        quick_sort_stack(&a, &b);
    }
    
    ft_putstr("Sorted stack: ");
    print_stack(a);
    
    free_stack(&a);
    free_stack(&b);
    
    return 0;
}