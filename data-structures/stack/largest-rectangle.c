#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'largestRectangle' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY h as parameter.
 */
 
 typedef struct Stack
 {
    int *data;
    int top;
    int size;
 } Stack;
 
 Stack *createStack(int size)
 {
    Stack *stack = (Stack *)malloc(size*sizeof(Stack));
    
    stack->data = (int *)malloc(size*sizeof(int));
    stack->top = -1;
    stack->size = size;
    
    return stack;
 }
 
 void push(Stack *s, int value)
 {
    if (s->top < s->size-1)
    {
        s->data[++s->top] = value;
    }
 }
 
 int pop(Stack *s)
 {
    if (s->top > -1)
    {
        return s->data[s->top--];
    }
    
    else {
        return -1;
    }
    
 }
 
 int isEmpty(Stack *s)
 {
    return s->top == -1;
 }
 
 int peek(Stack *s)
 {
    if (s->top >=0)
    {
        return s->data[s->top];
    }
    else {
        return -1;
    }
 }
 
 void freeStack(Stack *s)
 {
    free(s->data);
    free(s);
 }

long largestRectangle(int h_count, int* h) {
    Stack *index = createStack(h_count);
    Stack *height = createStack(h_count);
    long maxArea = 0;
    
    for (int i=0; i<h_count; i++)
    {
        int start = i;
        
        while (!isEmpty(height) && h[i]<peek(height))
        {
            int visina = pop(height);
            int indeks = pop(index);
            long area = (long) visina * (i - indeks);
            if (area > maxArea)
            {
                maxArea = area;
            }
            
            start = indeks;
        }
        
        push(height, h[i]);
        push(index, start);
    }
    
    while (!isEmpty(height))
    {
        int visina = pop(height);
        int indeks = pop(index);
        long area = (long) visina * (h_count - indeks);
        if (area > maxArea)
        {
            maxArea = area;
        }
    }
    
    free(height);
    free(index);
    
    return maxArea;
    
    
     
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** h_temp = split_string(rtrim(readline()));

    int* h = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int h_item = parse_int(*(h_temp + i));

        *(h + i) = h_item;
    }

    long result = largestRectangle(n, h);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

