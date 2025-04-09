#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  

char input[100];
int i = 0;

void error() {
    printf(" Error: Invalid syntax\n");
    exit(1);
}

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

void E();
void E_prime();
void T();
void T_prime();
void F();

void E() {
    T();
    E_prime();
}

void E_prime() {
    if (input[i] == '+') {
        match('+');
        T();
        E_prime();
    }
}

void T() {
    F();
    T_prime();
}

void T_prime() {
    if (input[i] == '*') {
        match('*');
        F();
        T_prime();
    }
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(input[i])) {
        match(input[i]);
    } else {
        error();
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    E();

    if (input[i] == '\0') {
        printf("Input is valid \n");
    } else {
        printf("Input is invalid.\n");
    }

    return 0;
}
