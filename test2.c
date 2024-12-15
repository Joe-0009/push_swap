#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct s_stack {
    int value;
    struct s_stack *next;
} s_stack;

// Custom implementations
int ft_atoi(const char *str);
void ft_putchar(char c);
void ft_putnbr(int n);
void ft_putstr(const char *str);
void ft_printf(const char *format, ...);

// Stack functions
s_stack *ft_new_node(int value);
void ft_add_back(s_stack **stack, s_stack *new_node);
int get_stack_size(s_stack *stack);
void free_stack(s_stack *stack);

// strtok implementation
char *ft_strtok(char *str, const char *delim);

char *ft_strchr(const char *str, int c) {
    while (*str) {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }

    // If c is '\0', we return the pointer to the null terminator
    if (c == '\0') {
        return (char *)str;
    }

    return NULL;
}
// Custom implementations
int ft_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespace
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r') {
        i++;
    }

    // Handle sign
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Convert characters to integer
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putnbr(int n) {
    if (n == -2147483648) {
        ft_putchar('-');
        ft_putchar('2');
        ft_putnbr(147483648);
        return;
    }

    if (n < 0) {
        ft_putchar('-');
        n = -n;
    }

    if (n >= 10) {
        ft_putnbr(n / 10);
    }
    ft_putchar(n % 10 + '0');
}

void ft_putstr(const char *str) {
    while (*str) {
        ft_putchar(*str);
        str++;
    }
}

void ft_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;  // Move past the '%' character
            
            if (*format == 'd') {
                int num = va_arg(args, int);
                ft_putnbr(num);
            }
        } else {
            ft_putchar(*format);
        }
        
        format++;
    }
    
    va_end(args);
}

// Stack functions
s_stack *ft_new_node(int value) {
    s_stack *new_node = malloc(sizeof(s_stack));
    if (!new_node)
        return NULL;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void ft_add_back(s_stack **stack, s_stack *new_node) {
    if (!*stack) {
        *stack = new_node;
    } else {
        s_stack *temp = *stack;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

void sa(s_stack **stack) {
    if (*stack && (*stack)->next) {
        s_stack *temp = (*stack)->next;
        (*stack)->next = temp->next;
        temp->next = *stack;
        *stack = temp;
        ft_printf("sa\n");
    }
}

void sb(s_stack **stack) {
    sa(stack);  // Simply call sa() on stack B
}

void pa(s_stack **stack_a, s_stack **stack_b) {
    if (*stack_b) {
        s_stack *temp = *stack_b;
        *stack_b = (*stack_b)->next;
        temp->next = *stack_a;
        *stack_a = temp;
        ft_printf("pa\n");
    }
}

void pb(s_stack **stack_a, s_stack **stack_b) {
    if (*stack_a) {
        s_stack *temp = *stack_a;
        *stack_a = (*stack_a)->next;
        temp->next = *stack_b;
        *stack_b = temp;
        ft_printf("pb\n");
    }
}

void ra(s_stack **stack) {
    if (*stack && (*stack)->next) {
        s_stack *temp = *stack;
        *stack = (*stack)->next;
        temp->next = NULL;
        s_stack *tail = *stack;
        while (tail->next)
            tail = tail->next;
        tail->next = temp;
        ft_printf("ra\n");
    }
}

void rra(s_stack **stack) {
    if (*stack && (*stack)->next) {
        s_stack *tail = *stack;
        while (tail->next)
            tail = tail->next;
        s_stack *second_last = *stack;
        while (second_last->next != tail)
            second_last = second_last->next;
        second_last->next = NULL;
        tail->next = *stack;
        *stack = tail;
        ft_printf("rra\n");
    }
}

int get_stack_size(s_stack *stack) {
    int size = 0;
    while (stack) {
        size++;
        stack = stack->next;
    }
    return size;
}

void free_stack(s_stack *stack) {
    s_stack *temp;
    while (stack) {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}

// strtok implementation
char *ft_strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    char *start;
    int i, j;

    // If str is NULL, continue from the last token
    if (str == NULL && next_token == NULL)
        return NULL;

    // Set start pointer if this is the first call
    if (str != NULL) {
        start = str;
    } else {
        start = next_token;
    }

    // Skip leading delimiters
    while (*start && ft_strchr(delim, *start)) {
        start++;
    }

    // If we reach the end of the string
    if (*start == '\0') {
        next_token = NULL;
        return NULL;
    }

    // Find the end of the token
    for (i = 0; start[i] != '\0' && !ft_strchr(delim, start[i]); i++) {}

    // Set next_token to point to the rest of the string after the token
    next_token = start + i;
    if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }

    return start;
}

int get_max_bits(s_stack *stack) {
    int max = 0;
    while (stack) {
        if (stack->value > max)
            max = stack->value;
        stack = stack->next;
    }
    int bits = 0;
    while (max > 0) {
        bits++;
        max >>= 1;
    }
    return bits;
}
int is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Already sorted
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void push(int *src, int *dst, int *src_size, int *dst_size) {
    if (*src_size == 0) return;
    dst[(*dst_size)++] = src[--(*src_size)];
}

void rotate(int *arr, int size) {
    if (size <= 1) return;
    int first = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = first;
}

void push_swap(int *arr, int size) {
    if (is_sorted(arr, size)) return;

    // Perform the sorting operations
    // Example: pushing and rotating as needed
    for (int i = 0; i < size; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr, i, i + 1);
        }
    }
}

void radix_sort(s_stack **stack_a, s_stack **stack_b) {
    int max_value = 0;
    s_stack *temp = *stack_a;

    // Find the maximum value in stack_a
    while (temp) {
        if (temp->value > max_value) {
            max_value = temp->value;
        }
        temp = temp->next;
    }

    int divisor = 1;  // Start with the least significant digit
    while (max_value / divisor > 0) {  // Continue until we process all digits
        int size = get_stack_size(*stack_a);
        int j = 0;

        // First loop: split elements based on the current digit
        while (j < size) {
            s_stack *temp = *stack_a;
            int value = temp->value;

            // Check the current digit (using modulus)
            if (value / divisor % 10 != 0) {
                pb(stack_a, stack_b);  // If the digit is non-zero, move the element to stack_b
            } else {
                ra(stack_a);  // Otherwise, rotate stack_a to move next element to the top
            }

            j++;  // Increment the counter for the inner loop
        }

        // Second loop: Push all elements back from stack_b to stack_a
        while (*stack_b) {
            pa(stack_a, stack_b);  // Push back to stack_a
        }

        divisor *= 10;  // Move to the next more significant digit
    }
}

int main(int argc, char *argv[]) {
    s_stack *stack_a = NULL;
    s_stack *stack_b = NULL;

    if (argc == 2) {
        // If one argument (a string), split it by spaces
        char *token = ft_strtok(argv[1], " ");
        while (token) {
            int num = ft_atoi(token);
            s_stack *new_node = ft_new_node(num);
            ft_add_back(&stack_a, new_node);
            token = ft_strtok(NULL, " ");
        }
    } else {
        // If multiple arguments, convert each argument to an integer
        for (int i = 1; i < argc; i++) {
            int num = ft_atoi(argv[i]);
            s_stack *new_node = ft_new_node(num);
            ft_add_back(&stack_a, new_node);
        }
    }

    // Sort the stack using radix sort
    radix_sort(&stack_a, &stack_b);

    // Free the stack after use
    free_stack(stack_a);
    free_stack(stack_b);
    return 0;
}
