#ifndef _LEXER_H_
#define _LEXER_H_

// size_t
#include <stddef.h>

#define MAX_TOKEN_LEN 256

typedef enum _TokenType_ {
    TOKEN_TYPE_NUMBER = 0,
    TOKEN_TYPE_ADD = 1,
    TOKEN_TYPE_SUBTRACT = 2,
    TOKEN_TYPE_MULTIPLY = 3,
    TOKEN_TYPE_DIVIDE = 4,
    TOKEN_TYPE_LPAR = 5,
    TOKEN_TYPE_RPAR = 6,
    TOKEN_TYPE_UNKNOWN = 7,
    TOKEN_TYPE_EOF = 8
} TokenType;

typedef struct _Token_ {
    TokenType type;
    int value;
} Token;

typedef struct _Lexer_ {
    char* data;
    size_t data_len;
    size_t pos;
} Lexer;

char* token_type_to_string(TokenType type);
char lexer_current(Lexer* lexer, size_t offset);
Token lexer_next_token(Lexer* lexer);

#endif // !_LEXER_H_
