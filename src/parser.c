#include <stdio.h>
#include <string.h>

#include "global.h"
#include "scanner.h"
#include "parser.h"
#include "table.h"
#include "dfa.h"
#include "utils.h"

 /**
  * 读头指针跟随自动机一起动。cur_col即读头指针
  * 自动机函数为有副作用的函数
  * parser可以写文件
 */
PRIVATE char token[TOKEN_SIZE];

PRIVATE int cur_line, cur_col;

PRIVATE void parser_reset();
PRIVATE void token_print();


PUBLIC void parser_init() {
    cur_line = 0;
    cur_col = 0;
    symbol_table_init();
}

// PUBLIC void parse_error()
PUBLIC void parse_str(char* str, int line) {
    int err = general_dfa(str, &cur_col, token);
    if(err) {
        parse_error();
    }
    // token_print();
}

PUBLIC void parser_write(FILE* dest) {
    fputs(token, dest);
    parser_reset();
}

PUBLIC void parse_error() {
    printf("parser error!\n");
    printf("in (line, col):(%d, %d)\n", cur_line, cur_col);
    printf("parser stop!\n");
}

PRIVATE void parser_reset() {
    cur_line = 0;
    cur_col = 0;
    strclr(token);
}

PRIVATE void token_print() {
    printf(token);
}