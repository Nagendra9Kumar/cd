#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Check if character is a delimiter
bool isDelimiter(char ch) {
    return strchr(" ,;(){}[]=<>", ch) != NULL;
}

// Check if character is an operator
bool isOperator(char ch) {
    return strchr("+-*/=<>", ch) != NULL;
}

// Check if string is a keyword
bool isKeyword(const char *str) {
    const char *keywords[] = {"int", "float", "if", "else", "while", "return", "char", "void"};
    for (int i = 0; i < 8; i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

// Check if string is a valid identifier
bool isValidIdentifier(const char *str) {
    return (isalpha(str[0]) || str[0] == '_');
}

// Check if string is an integer
bool isInteger(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (isdigit(str[i])) return true;
    return false;
}

// Extract substring
char *subString(const char *str, int left, int right) {
    static char subStr[50];
    strncpy(subStr, str + left, right - left);
    subStr[right - left] = '\0';
    return subStr;
}

// Parse input string
void parse(const char *str) {
    int left = 0, right = 0, len = strlen(str);

    while (right <= len) {
        if (!isDelimiter(str[right]) && str[right] != '\0') {
            right++;
        } else {
            if (left != right) {
                char *token = subString(str, left, right);
                if (isKeyword(token)) 
                    printf("'%s' is a KEYWORD\n", token);
                else if (isInteger(token))
                    printf("'%s' is an INTEGER\n", token);
                else if (isValidIdentifier(token))
                    printf("'%s' is an IDENTIFIER\n", token);
                else
                    printf("'%s' is INVALID\n", token);
            }
            if (isOperator(str[right])) 
                printf("'%c' is an OPERATOR\n", str[right]);

            right++;
            left = right;
        }
    }
}

int main() {
    char str[] = "int a = 10;";
    parse(str);
    return 0;
}
