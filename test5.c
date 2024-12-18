/* push_swap.h */
#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
// Stack structure
typedef struct s_stack {
    int *array;
    int top;
    int size;
} t_stack;

// Function prototypes for stack operations
void sa(t_stack *a);
void sb(t_stack *b);
void ss(t_stack *a, t_stack *b);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);

// Input validation and parsing
int validate_input(int argc, char **argv);
int parse_input(int argc, char **argv, t_stack *a);

// Sorting algorithms
void sort_two(t_stack *a);
void sort_three(t_stack *a);
void sort_five(t_stack *a, t_stack *b);
void chunk_sort(t_stack *a, t_stack *b);

// Utility functions
int is_sorted(t_stack *stack);
void error_exit(const char *msg);
int find_min_moves(t_stack *a, int chunk_start, int chunk_end);
void move_to_top(t_stack *a, int index, int list_mid);
int find_index(t_stack *a, int chunk_start, int chunk_end);
int find_best_insertion_point(t_stack *b, int num);


// printer 
void print_stack(t_stack *stack, const char *label);


#endif // PUSH_SWAP_H

/* In sorting_algorithms.c, add this function */
void print_stack(t_stack *stack, const char *label) {
    printf("%s Stack: ", label);
    if (stack->top == -1) {
        printf("Empty\n");
        return;
    }
    
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

/* stack_ops.c - Same as previous implementation */


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


/* input_validation.c - Same as previous implementation */

int is_valid_number(const char *str) {
    int i = 0;
    if (str[i] == '-' || str[i] == '+') i++;
    
    if (strlen(str + i) > 10) return 0;  // Potential overflow
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') return 0;
        i++;
    }
    
    long long num = atoll(str);
    return (num >= INT_MIN && num <= INT_MAX);
}

int check_duplicates(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) return 1;
        }
    }
    return 0;
}

int validate_input(int argc, char **argv) {
    int total_count = 0;
    
    for (int i = 1; i < argc; i++) {
        char *token;
        char *str = strdup(argv[i]);
        char *saveptr;
        
        token = strtok_r(str, " ", &saveptr);
        while (token) {
            if (!is_valid_number(token)) {
                free(str);
                return 0;
            }
            total_count++;
            token = strtok_r(NULL, " ", &saveptr);
        }
        free(str);
    }
    
    return total_count;
}

int parse_input(int argc, char **argv, t_stack *a) {
    int total_count = validate_input(argc, argv);
    if (total_count == 0) return 0;
    
    a->array = malloc(sizeof(int) * total_count);
    a->size = total_count;
    a->top = -1;
    
    int index = total_count - 1;
    
    for (int i = 1; i < argc; i++) {
        char *token;
        char *str = strdup(argv[i]);
        char *saveptr;
        
        token = strtok_r(str, " ", &saveptr);
        while (token) {
            a->array[index--] = atoi(token);
            a->top++;
            token = strtok_r(NULL, " ", &saveptr);
        }
        free(str);
    }
    
    if (check_duplicates(a->array, a->size)) {
        free(a->array);
        return 0;
    }
    
    return 1;
}


/* sorting_algorithms.c */

int is_sorted(t_stack *stack) {
    for (int i = 0; i < stack->top; i++) {
        if (stack->array[i] > stack->array[i+1]) 
            return 0;
    }
    return 1;
}

void sort_two(t_stack *a) {
    if (a->array[a->top] < a->array[a->top - 1])
        sa(a);
}

void sort_three(t_stack *a) {
    int max = a->array[a->top];
    int mid = a->array[a->top - 1];
    int min = a->array[a->top - 2];

    if (max < mid && max < min) { ra(a); }
    if (mid < max && mid < min) { rra(a); }
    
    if (a->array[a->top] > a->array[a->top - 1])
        sa(a);
}

void sort_five(t_stack *a, t_stack *b) {
    while (a->top > 2) {
        pb(a, b);
    }
    
    sort_three(a);
    
    if (b->top > 0 && b->array[b->top] < b->array[b->top - 1])
        sb(b);
    
    pa(a, b);
    pa(a, b);
}

void radix_sort(t_stack *a, t_stack *b) {
    int max_num = a->array[0];
    for (int i = 1; i <= a->top; i++) {
        if (a->array[i] > max_num)
            max_num = a->array[i];
    }

    for (int shift = 1; max_num / shift > 0; shift *= 10) {
        int n = a->top + 1;
        for (int i = 0; i < n; i++) {
            pb(a, b);
        }

        while (b->top != -1) {
            int current = b->array[b->top];
            if (((current / shift) % 10) == 0) {
                pa(a, b);
            } else {
                rb(b);
            }
        }
    }
}

int find_index(t_stack *a, int chunk_start, int chunk_end) {
    for (int i = 0; i <= a->top; i++) {
        if (a->array[a->top - i] >= chunk_start && a->array[a->top - i] <= chunk_end)
            return i;
    }
    return -1;
}

void move_to_top(t_stack *a, int index, int list_mid) {
    if (index <= list_mid) {
        // Use ra
        for (int i = 0; i < index; i++)
            ra(a);
    } else {
        // Use rra
        for (int i = 0; i < (a->top + 1 - index); i++)
            rra(a);
    }
}

int find_min_moves(t_stack *a, int chunk_start, int chunk_end) {
    int list_mid = a->top / 2;
    int first_index = -1, second_index = -1;

    // Find first number in chunk from top
    for (int i = 0; i <= a->top; i++) {
        if (a->array[a->top - i] >= chunk_start && a->array[a->top - i] <= chunk_end) {
            first_index = i;
            break;
        }
    }

    // Find first number in chunk from bottom
    for (int i = 0; i <= a->top; i++) {
        if (a->array[i] >= chunk_start && a->array[i] <= chunk_end) {
            second_index = a->top + 1 - i;
            break;
        }
    }

    // If no number found in chunk
    if (first_index == -1)
        return -1;

    // Determine which index requires fewer moves
    return (first_index <= list_mid) ? first_index : (a->top + 1 - first_index);
}

int find_best_insertion_point(t_stack *b, int num) {
    if (b->top == -1) return 0;

    for (int i = 0; i <= b->top; i++) {
        if (num > b->array[b->top - i]) 
            return i;
    }
    return b->top + 1;
}
void chunk_sort(t_stack *a, t_stack *b) {
    // Variable declarations at the start
    int total_nums;
    int chunk_size;
    int chunk_start;
    int chunk_end;
    int list_mid;
    int index;
    int insert_point;
    int max_index;
    int max_value;

    // Initialize variables
    total_nums = a->top + 1;
    chunk_size = total_nums / 11;  // Divide into 11 chunks
    list_mid = total_nums / 2;
    
    // First pass: distribute numbers into chunks
    chunk_start = 0;
    while (chunk_start < 11) {
        // Calculate chunk boundaries
        chunk_end = (chunk_start == 10) ? total_nums - 1 : (chunk_start + 1) * chunk_size - 1;

        // Find and move numbers in this chunk to stack B
        index = find_index(a, chunk_start * chunk_size, chunk_end);
        if (index == -1) {
            chunk_start++;
            continue;
        }

        // Move the number to the top of stack A
        move_to_top(a, index, list_mid);

        // Find best insertion point in Stack B
        insert_point = find_best_insertion_point(b, a->array[a->top]);

        // Push to Stack B
        pb(a, b);
    }

    // Second pass: reinsert from B to A in sorted order
    while (b->top != -1) {
        // Reset list mid for B's current size
        list_mid = b->top / 2;
        
        // Find maximum in stack B
        max_index = 0;
        max_value = b->array[b->top];
        
        // Manual max search without loop
        if (b->top > 0 && b->array[b->top - 1] > max_value) {
            max_index = 1;
            max_value = b->array[b->top - 1];
        }
        
        if (b->top > 1 && b->array[b->top - 2] > max_value) {
            max_index = 2;
            max_value = b->array[b->top - 2];
        }
        
        // Continue comparing and updating max_index if stack is larger
        if (b->top > 2) {
            int current_index = 3;
            while (current_index <= b->top) {
                if (b->array[b->top - current_index] > max_value) {
                    max_index = current_index;
                    max_value = b->array[b->top - current_index];
                }
                current_index++;
            }
        }

        // Move max to top
        move_to_top(b, max_index, list_mid);
        
        // Push back to A
        pa(a, b);
    }
}

/* main.c */

void error_exit(const char *msg) {
    write(2, msg, strlen(msg));
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 2) return 0;
    
    t_stack a = {0}, b = {0};
    
    if (!parse_input(argc, argv, &a)) {
        error_exit("Error\n");
    }
    
    if (is_sorted(&a)) {
        free(a.array);
        return 0;
    }
    
    // Print initial stack
    printf("Initial Stack:\n");
    print_stack(&a, "A");
    
    b.array = malloc(sizeof(int) * a.size);
    b.size = a.size;
    b.top = -1;
    
    switch (a.top + 1) {
        case 1: break;
        case 2: sort_two(&a); break;
        case 3: sort_three(&a); break;
        case 4:
        case 5: sort_five(&a, &b); break;
        default: chunk_sort(&a, &b);
    }
    
    // Print final sorted stack
    printf("\nFinal Sorted Stack:\n");
    print_stack(&a, "A");
    print_stack(&b, "B");
    
    // Verify sorting
    printf("\nIs Stack A Sorted? %s\n", is_sorted(&a) ? "Yes" : "No");
    
    free(a.array);
    free(b.array);
    
    return 0;
}