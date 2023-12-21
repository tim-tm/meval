#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>

static char* substr(int start, int end, char* str) {
    if (!str) return NULL;
    char* substring = calloc(sizeof(char), end);
    int i = 0;
    while (i < end) {
        substring[i] = str[start+i];
        ++i;
    }
    substring[i] = '\0';
    return substring;
}

char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_ADD: {
            return "TOKEN_TYPE_ADD";
        } break;
        case TOKEN_TYPE_SUBTRACT: {
            return "TOKEN_TYPE_SUBTRACT";
        } break;
        case TOKEN_TYPE_MULTIPLY: {
            return "TOKEN_TYPE_MULTIPLY";
        } break;
        case TOKEN_TYPE_DIVIDE: {
            return "TOKEN_TYPE_DIVIDE";
        } break;
        case TOKEN_TYPE_NUMBER: {
            return "TOKEN_TYPE_NUMBER";
        } break;
        case TOKEN_TYPE_UNKNOWN: {
            return "TOKEN_TYPE_UNKNOWN";
        } break;
        case TOKEN_TYPE_EOF: {
            return "TOKEN_TYPE_EOF";
        } break;
        case TOKEN_TYPE_LPAR: {
            return "TOKEN_TYPE_LPAR";
        } break;
        case TOKEN_TYPE_RPAR: {
            return "TOKEN_TYPE_RPAR";
        } break;
        default: {
            return "INVALID_TOKEN";
        } break;
    }
}

char lexer_current(Lexer* lexer, size_t offset) {
    if (!lexer || (lexer->pos+offset) >= lexer->data_len) return '\0';
    return lexer->data[(lexer->pos+offset)];
}

Token lexer_next_token(Lexer* lexer) {
    if (lexer->pos >= lexer->data_len) {
        return (Token){TOKEN_TYPE_EOF, 0};
    }
    if (isspace(lexer_current(lexer, 0))) {
        size_t i = 0;
        while (isspace(lexer_current(lexer, i))) {
            ++i;
        }
        lexer->pos += i;
    }
    if (isdigit(lexer_current(lexer, 0))) {
        size_t i = 0;
        while (isdigit(lexer_current(lexer, i))) {
            ++i;
        }
        
        char* substring = substr(lexer->pos, lexer->pos+i, lexer->data);
        int parsed = atoi(substring);
        lexer->pos += i;
        return (Token){TOKEN_TYPE_NUMBER, parsed};
    }

    Token t;
    switch (lexer_current(lexer, 0)) {
        case '+': {
            t = (Token){TOKEN_TYPE_ADD, 0};
            lexer->pos++;    
        } break;
        case '-': {
            t = (Token){TOKEN_TYPE_SUBTRACT, 0};
            lexer->pos++;    
        } break;
        case '*': {
            t = (Token){TOKEN_TYPE_MULTIPLY, 0};
            lexer->pos++;    
        } break;
        case '/': {
            t = (Token){TOKEN_TYPE_DIVIDE, 0};
            lexer->pos++;    
        } break;
        case '(': {
            t = (Token){TOKEN_TYPE_LPAR, 0};
            lexer->pos++;    
        } break;
        case ')': {
            t = (Token){TOKEN_TYPE_RPAR, 0};
            lexer->pos++;    
        } break;
        default: {
            t = (Token){TOKEN_TYPE_UNKNOWN, -1};
            lexer->pos++;    
        } break;
    }
    return t;
}
