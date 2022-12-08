#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "global.h"
#include "table.h"

/**
 * 符号表相关操作，增，删，查
 */

PRIVATE struct symbol_table_node *symbol_table, *symbol_table_tail;
PRIVATE struct alias_table_node *alias_table, *alias_table_tail;
PRIVATE int symbol_table_cnt, alias_table_cnt;
  

PUBLIC void symbol_table_init() {
    symbol_table_tail = symbol_table = NULL;
    alias_table_tail = alias_table = NULL;
    symbol_table_cnt = alias_table_cnt = 0;
}


PUBLIC void symbol_table_destroy() {
    struct symbol_table_node* p = symbol_table;

    while (p != NULL) {
        if (p->addr != NULL) free(p->addr);
        free(p);
        p = p->next;
    }

}

PUBLIC void symbol_table_print() {
    struct symbol_table_node* p = symbol_table;
    while (p != NULL) {
        printf("%10s, %10d, %10s\n", p->name, p->symbol_type, p->type);
        p = p->next;
    }
}


PUBLIC int put_symbol_table(char* name, int symbol_type, struct token_location* location, int type) {
    struct symbol_table_node* st_node;

    st_node = (struct symbol_table_node*)malloc(sizeof(struct symbol_table_node));
    strcpy(st_node->name, name);
    st_node->symbol_type = symbol_type;
    st_node->type = type;
    st_node->addr = location;
    st_node->next = NULL;
    if (symbol_table_tail == NULL) {
        symbol_table = symbol_table_tail = st_node;
    }
    else {
        symbol_table_tail->next = st_node;
    }
    symbol_table_tail = st_node;
    return symbol_table_cnt++;
}


PUBLIC struct token_location* get_location(char* token) {
    
}