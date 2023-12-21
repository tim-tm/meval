#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

typedef struct _StackNode_ {
    Token token;
    struct _StackNode_* next;
} StackNode;

typedef struct _Parser_ {
    StackNode* top_node;
    int result;
} Parser;

Parser* parser_init(Lexer* lexer);
void parser_eval(Parser* parser);
void parser_destroy(Parser* parser);

#endif // !_PARSER_H_
