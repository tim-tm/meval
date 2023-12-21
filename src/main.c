#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

int main(void) {
    char* str = NULL;
    size_t size = 0;
    while (getline(&str, &size, stdin) != -1) {
        Lexer lexer = {
            .data = str,
            .data_len = strnlen(str, MAX_TOKEN_LEN),
            .pos = 0
        };
        Parser* parser = parser_init(&lexer);
        if (!parser) {
            printf("Invalid expression!\n");
            parser_destroy(parser);
            return -1;
        }
        parser_eval(parser);
        printf("%i\n", parser->result);
        parser_destroy(parser);
    }
    return 0;
}

