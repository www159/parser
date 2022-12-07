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

    struct alias_table_node *q = alias_table;
    while (q != NULL) {
        if (q->addr != NULL) free(q->addr);
        free(q);
        q = q->next;
    }
}

PUBLIC void symbol_table_print() {
    struct symbol_table_node* p = symbol_table;
    while (p != NULL) {
        printf("%10s, %10d, %10s\n", p->name, p->symbol_type, p->type);
        p = p->next;
    }
}

PUBLIC void put_symbol_table(char* name, int symbol_type, struct token_location* location, char* type, char* token) {
    struct symbol_table_node* st_node;
    struct alias_table_node* at_node;
    int token_cnt;

    switch (symbol_type) {
        case FUNCT:
        case VAR:
            st_node = (struct symbol_table_node*)malloc(sizeof(struct symbol_table_node));
            strcpy(st_node->name, name);
            st_node->symbol_type = symbol_type;
            strcpy(st_node->type, type);
            st_node->addr = location;
            st_node->next = NULL;
            if (symbol_table_tail == NULL) {
                symbol_table = symbol_table_tail = st_node;
            }
            else {
                symbol_table_tail->next = st_node;
            }
            symbol_table_tail++;
            token_cnt = symbol_table_cnt++;
            break;
        case IMM:
        case OPERATOR:
        case KEYWORD:
            at_node = (struct alias_table_node*)malloc(sizeof(struct alias_table_node));
            at_node->addr = location;
            at_node->next = NULL;
            if (alias_table_tail == NULL) {
                alias_table = alias_table_tail = at_node;
            }
            else {
                alias_table_tail->next = at_node;
            }
            alias_table_tail++;
            token_cnt = alias_table_cnt++;
            break;
    }

    sprintf(token, "<%d,%d>", symbol_type, token_cnt);
    
}


PUBLIC struct token_location* get_location(char* token) {

}