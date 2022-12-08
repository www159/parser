#include "global.h"
#include "table.h"

#include <stdio.h>
int main() {
    printf("parse start\n");
    symbol_table_init();
    printf("test symbol_table\n");
    char token[200];
    put_symbol_table("hh123", VAR, NULL, "int32", token);
    symbol_table_print();
    printf("token is %s\n", token);
    printf("test alias_table\n");
    put_symbol_table("while", KEYWORD, NULL, NULL, token);
    symbol_table_print();
    symbol_table_destroy();
    
    printf("parse done\n");
    return 0;
}