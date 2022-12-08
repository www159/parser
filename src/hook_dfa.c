#include <stdio.h>

#include "global.h"
#include "hook_dfa.h"
#include "token.h"
#include "table.h"

PUBLIC void while_hook(char* token, char* _) {
    set_token(token, KEYWORD, WHILE, NULL);
}

PUBLIC void for_hook(char* token, char* _) {
    set_token(token, KEYWORD, FOR, NULL);
}

PUBLIC void if_hook(char* token, char* _) {
    set_token(token, KEYWORD, IF, NULL);
}

PUBLIC void else_hook(char* token, char* _) {
    set_token(token, KEYWORD, ELSE, NULL);
}

PUBLIC void identifier_hook(char* token, char* name) {
    set_token(token, VAR, NULL_INT, name);
}