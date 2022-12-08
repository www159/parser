// #include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "token.h"
#include "table.h"

PUBLIC void set_token(char* token, int symbol_type, int type, char* name) {
    char single_token[SINGLE_TOKEN_SIZE];
    int pos;

    switch (symbol_type) {
        case FUNCT:
        case VAR:
        case IMM:
            pos = put_symbol_table(name, symbol_type, NULL, type);
            sprintf(single_token, "<%d,%d>", symbol_type, pos);
            break;
        
        case KEYWORD:
        case OPERATOR:
            sprintf(single_token, "<%d,->", type);
            break;
        default:
            break;
    }

    strcat(token, single_token);
}