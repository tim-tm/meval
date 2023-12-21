#include "parser.h"
#include <stdlib.h>

static void stack_push(Parser* parser, Token value) {
    if (!parser) return;

    StackNode* next = malloc(sizeof(StackNode));
    next->token = value;
    next->next = parser->top_node;
    parser->top_node = next;
}

static StackNode* stack_pop(Parser* parser) {
    StackNode* val = parser->top_node;
    parser->top_node = parser->top_node->next;
    return val;
}

Parser* parser_init(Lexer* lexer) {
    if (!lexer) return NULL;
    Parser* par = malloc(sizeof(Parser));
    par->top_node = malloc(sizeof(StackNode));

    Token token = lexer_next_token(lexer);
    Token last_operation;
    while (token.type != TOKEN_TYPE_EOF) {
        switch (token.type) {
            case TOKEN_TYPE_NUMBER: {
                if (last_operation.type == TOKEN_TYPE_ADD) {
                    Token one = stack_pop(par)->token;
                    if (one.type == TOKEN_TYPE_NUMBER) {
                        Token result = (Token){
                            .type = TOKEN_TYPE_NUMBER,
                            .value = one.value + token.value
                        };
                        stack_push(par, result);
                    } else {
                        parser_destroy(par);
                        return NULL;
                    }
                } else if (last_operation.type == TOKEN_TYPE_SUBTRACT) {
                    Token one = stack_pop(par)->token;
                    if (one.type == TOKEN_TYPE_NUMBER) {
                        Token result = (Token){
                            .type = TOKEN_TYPE_NUMBER,
                            .value = one.value - token.value
                        };
                        stack_push(par, result);
                    } else {
                        parser_destroy(par);
                        return NULL;
                    }
                } else if (last_operation.type == TOKEN_TYPE_MULTIPLY) {
                    Token one = stack_pop(par)->token;
                    if (one.type == TOKEN_TYPE_NUMBER) {
                        Token result = (Token){
                            .type = TOKEN_TYPE_NUMBER,
                            .value = one.value * token.value
                        };
                        stack_push(par, result);
                    } else {
                        parser_destroy(par);
                        return NULL;
                    }
                } else if (last_operation.type == TOKEN_TYPE_DIVIDE) {
                    Token one = stack_pop(par)->token;
                    if (one.type == TOKEN_TYPE_NUMBER) {
                        Token result = (Token){
                            .type = TOKEN_TYPE_NUMBER,
                            .value = one.value / token.value
                        };
                        stack_push(par, result);
                    } else {
                        parser_destroy(par);
                        return NULL;
                    }
                } else {
                    stack_push(par, token);
                }
            } break;
            case TOKEN_TYPE_ADD:
            case TOKEN_TYPE_SUBTRACT:
            case TOKEN_TYPE_MULTIPLY:
            case TOKEN_TYPE_DIVIDE: {
                last_operation = token;
            } break;
            /*case TOKEN_TYPE_UNKNOWN: {
                parser_destroy(par);
                return NULL;
            } break;*/
            default: {
            } break;
        }
        token = lexer_next_token(lexer);
    }
    return par;
}

void parser_eval(Parser* parser) {
    if (!parser) return;
    parser->result = stack_pop(parser)->token.value;
}

void parser_destroy(Parser* parser) {
    if (parser) {
        StackNode* node = stack_pop(parser);
        while (node) {
            StackNode* n = node->next;
            free(node);
            node = n;
        }
        free(parser);
    }
}
