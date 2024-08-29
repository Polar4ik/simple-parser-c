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
    int value;  // use only for number
} Token;

typedef struct ASTNode {
    TokenType type;
    int value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

char *input;
int pos = 0;

Token get_next_token() {
    Token token;

    // pass whitespace
    while (isspace(input[pos])) pos++;

    if (isdigit(input[pos])) {
        token.type = TOKEN_NUMBER;
        token.value = input[pos] - '0'; // to number
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

ASTNode *new_ast_node(TokenType token, int value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = token;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *parse_exp() {
    Token token = get_next_token();

    if (token.type == TOKEN_NUMBER) {
        ASTNode *node = new_ast_node(TOKEN_NUMBER, token.type);
        token = get_next_token();

        while (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
            ASTNode *op_node = new_ast_node(token.type, 0);

            op_node->left = node;
            op_node->right = new_ast_node(TOKEN_NUMBER, get_next_token().value);
            
            node = op_node;
            token = get_next_token();
        }

        return node;
    }

    return NULL;
}

int main() {
    input = "2+2";
    ASTNode *ast = parse_exp();

    return 0;
}
