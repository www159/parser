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

/**
 * @brief 将字符串转成字符流，并存到缓冲区
 * 为多趟铺垫
 * @param str 待转换的字符串
 * @param line 当前文件行数
*/
PUBLIC void parse_str(char* str, int line);

/**
 * @brief 将缓冲区的字符输出到文件中
 * @param dest 输出的文件路径
*/
PUBLIC void parser_write(FILE* dest);

PUBLIC void parser_error();
#endif