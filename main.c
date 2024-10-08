#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TOKEN_NUMBER,
    
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

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
        
        char *start = &input[pos];

        while (isdigit(input[pos])) pos++;
        
        int len = &input[pos] - start;
        char *raw = (char *)malloc(len + 1);

        strncpy(raw, start, len);
        raw[len] = '\0';
	
        token.value = atoi(raw); // to number
        printf("NUM TOKEN, Token value: %d \n", token.value);
        
        free(raw);

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

    if (input[pos] == '*') {
        token.type = TOKEN_STAR;
        pos++;
        printf("STAR TOKEN\n");
        return token;
    }

    if (input[pos] == '/') {
        token.type = TOKEN_SLASH;
        pos++;
        printf("SLASH TOKEN\n");
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
        ASTNode *node = new_ast_node(TOKEN_NUMBER, token.value);
        token = get_next_token();

        if (token.type == TOKEN_STAR || token.type == TOKEN_SLASH)
        {
            ASTNode *op_node = new_ast_node(token.type, 0);

            op_node->left = node->right;
            op_node->right = new_ast_node(TOKEN_NUMBER, get_next_token().value);

            node->right = op_node;
            token = get_next_token();
        }

        if (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
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

int eval(ASTNode *node) {
    if (node->type == TOKEN_NUMBER) {
        return node->value;
    }

    int left_value = eval(node->left);
    int right_value = eval (node->right);

    if (node->type == TOKEN_PLUS) {
        return left_value + right_value;
    } else if (node->type == TOKEN_MINUS) {
        return left_value - right_value;
    }
    else if (node->type == TOKEN_STAR) {
        return left_value * right_value;
    }
    else if (node->type == TOKEN_SLASH) {
        return left_value / right_value;
    }

    return 0;
}

int main() {
    input = "2+2*2";
    ASTNode *ast = parse_exp();

    int res = eval(ast);
    printf("RES: %d", res);

    return 0;
}
