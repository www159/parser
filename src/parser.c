#include <stdio.h>
#include <string.h>

#include "global.h"
#include "scanner.h"
#include "parser.h"
#include "dfa.h"
#include "table.h"
#include "utils.h"

 /**
  * 读头指针跟随自动机一起动。cur_col即读头指针
  * 自动机函数为有副作用的函数
  * parser可以写文件
 */
// PRIVATE char* str_to_be_parsed[STR_SIZE];
PRIVATE char* token[TOKEN_SIZE];

PRIVATE int cur_line, cur_col;

PRIVATE void parser_reset();
PRIVATE void token_print();


PUBLIC void parser_init() {
    cur_line = 0;
    cur_col = 0;
    symbol_table_init();
}

PUBLIC void parse_str(char* str, int line) {
    parser_reset();
    general_dfa(str, &cur_col, token);
    token_print();
}

PRIVATE void parser_reset() {
    cur_line = 0;
    cur_col = 0;
    strclr(token);
}

PRIVATE void token_print() {
    printf(token);
}