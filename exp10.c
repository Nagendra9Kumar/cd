#include <stdio.h>
#include <string.h>

#define MAX 100

int shift_reduce_parse(char input[]) {
    char stack[MAX];
    int top = -1, i = 0;

    while (input[i] != '\0') {
        stack[++top] = input[i++];
        stack[top + 1] = '\0';
        printf("Shift:   %s\n", stack);

        int reduced;
        do {
            reduced = 0;

            if (top >= 1 && stack[top - 1] == 'a' && stack[top] == 'b') {
                top -= 1;
                stack[top] = 'S';
                stack[top + 1] = '\0';
                printf("Reduce:  %s (ab -> S)\n", stack);
                reduced = 1;
            } else if (top >= 2 && stack[top - 2] == 'a' && stack[top - 1] == 'S' && stack[top] == 'b') {
                top -= 2;
                stack[top] = 'S';
                stack[top + 1] = '\0';
                printf("Reduce:  %s (aSb -> S)\n", stack);
                reduced = 1;
            }

        } while (reduced);
    }

    return (top == 0 && stack[top] == 'S');
}

int main() {
    char input[MAX];

    printf("Enter input string: ");
    scanf("%s", input);

    if (shift_reduce_parse(input))
        printf("Input string accepted.\n");
    else
        printf("Input string rejected.\n");

    return 0;
}
