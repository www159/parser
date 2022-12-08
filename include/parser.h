#ifndef _W_PARSER_H_
#define _W_PARSER_H_

#define STR_SIZE BUFFER_SIZE
#define TOKEN_SIZE (STR_SIZE<<2)
/**
 * parser 处理字符串
 * parser存储了行，列。因此负责
 * 1. 报错
 * 2. 缓存token或者打印token
*/

PUBLIC void parser_init();
PUBLIC void parse_str(char* str, int line);
#endif