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
        token.value = input[pos] - '0'; // в число
        pos++;
        printf("NUM TOKEN, Token value: %d \n", token.value);
        return token;
    }

    if (input[pos] == '+') {
        token.type = TOKEN_PLUS;
        pos++;
        printf("PLUS TOKEN\n");
        return token;
    }

    if (input[pos] == '-') {
        token.type = TOKEN_MINUS;
        pos++;
        printf("MINUS TOKEN\n");
        return token;
    }

    token.type = TOKEN_EOF;
    return token;
}

int main() {
    input = "2+2";
    
    get_next_token();
    get_next_token();
    get_next_token();
    get_next_token();

    return 0;
}
