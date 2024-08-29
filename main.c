#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType type;
    int value;  // используется только для чисел
} Token;

char *input;
int pos = 0;

Token get_next_token() {
    Token token;

    // пропускаем пробелы
    while (isspace(input[pos])) pos++;

    if (isdigit(input[pos])) {
        token.type = TOKEN_NUMBER;
        token.value = input[pos] - 0; // в число
        pos++;
        printf("\nNUM TOKEN, Token value: %d", token.value);
        return token;
    }

    if (input[pos] == '+') {
        token.type = TOKEN_PLUS;
        pos++;
        printf("\nPLUS TOKEN");
        return token;
    }

    if (input[pos] == '-') {
        token.type = TOKEN_MINUS;
        pos++;
        printf("\nMINUS TOKEN");
        return token;
    }

    token.type = TOKEN_EOF;
    return token;
}




int main() {
    input = "2+2";
    return 0;
}
