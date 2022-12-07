#include "global.h"
#include "table.h"

#include <stdio.h>
int main() {
    printf("parse start\n");
    symbol_table_init();
    printf("test symbol_table\n");
    char token[200];
    put_symbol_table("hh123", 0, NULL, "int32", token);
    symbol_table_print();
    printf("token is %s\n", token);
    symbol_table_destroy();
    printf("test alias_table\n");
    put_symbol_table("while", 2, NULL, NULL, token);
    printf("parse done\n");
    return 0;
}