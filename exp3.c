#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int isDelimiter(char ch) {
    return strchr(" +-*/;,><=()[]{}", ch) != NULL;
}

int isOperator(char ch) {
    return strchr("+-*/><=", ch) != NULL;
}

int isKeyword(const char* str) {
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue", "int", "double",
        "float", "return", "char", "case", "sizeof", "long", "short", "typedef",
        "switch", "unsigned", "void", "static", "struct", "goto"
    };
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

int isMatch(const char* pattern, const char* str) {
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED);
    int result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

int validIdentifier(const char* str) {
    return isMatch("^[a-zA-Z_][a-zA-Z0-9_]*$", str);
}

int isInteger(const char* str) {
    return isMatch("^-?[0-9]+$", str);
}

int isRealNumber(const char* str) {
    return isMatch("^-?[0-9]*\\.[0-9]+$", str);
}

void parse(const char* str) {
    char token[100];
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (!isDelimiter(str[i])) {
            token[j++] = str[i++];
        } else {
            if (j != 0) {
                token[j] = '\0';
                if (isKeyword(token)) printf("'%s' IS A KEYWORD\n", token);
                else if (isInteger(token)) printf("'%s' IS AN INTEGER\n", token);
                else if (isRealNumber(token)) printf("'%s' IS A REAL NUMBER\n", token);
                else if (validIdentifier(token)) printf("'%s' IS A VALID IDENTIFIER\n", token);
                else printf("'%s' IS NOT A VALID IDENTIFIER\n", token);
                j = 0;
            }

            if (isOperator(str[i])) {
                printf("'%c' IS AN OPERATOR\n", str[i]);
            }
            i++;
        }
    }
}

int main() {
    const char* str = "float y = 1a+b-c;";
    parse(str);
    return 0;
}
