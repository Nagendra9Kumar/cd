#include <stdio.h>
#include <string.h>

char stack[100], input[100], action[] = "SHIFT";
int i = 0, j = 0, len;

void printState() {
    printf("\n$%s\t%s$\t", stack, input);
}

void reduce() {
    for (int k = 0; k < len - 2; k++) {
        if (stack[k] == '2' && stack[k + 1] == 'E' && stack[k + 2] == '2') {
            printf("REDUCE 2E2->E");
            stack[k] = 'E';
            stack[k + 1] = '\0';
            stack[k + 2] = '\0';
            printState();
            i -= 2;
            return;
        }
    }
    for (int k = 0; k < len - 2; k++) {
        if (stack[k] == '3' && stack[k + 1] == 'E' && stack[k + 2] == '3') {
            printf("REDUCE 3E3->E");
            stack[k] = 'E';
            stack[k + 1] = '\0';
            stack[k + 2] = '\0';
            printState();
            i -= 2;
            return;
        }
    }
    for (int k = 0; k < len; k++) {
        if (stack[k] == '4') {
            printf("REDUCE 4->E");
            stack[k] = 'E';
            printState();
            return;
        }
    }
}

int main() {
    printf("GRAMMAR:\nE -> 2E2\nE -> 3E3\nE -> 4\n");
    strcpy(input, "32423");
    len = strlen(input);

    printf("\nSTACK\tINPUT\tACTION");
    printState();

    while (j < len) {
        stack[i++] = input[j];
        stack[i] = '\0';
        input[j++] = ' ';
        printf("SHIFT");
        printState();
        reduce();
    }

    reduce();  // Final check

    if (strcmp(stack, "E") == 0)
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}
