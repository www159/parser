#ifndef _W_TOKEN_H_
#define _W_TOKEN_H_

/**
 * @brief 在token串后增加新的token，需要用到符号表就用符号表
*/
#define SINGLE_TOKEN_SIZE 40
PUBLIC void set_token(char* token, int symbol_type, int type, char* name);
#endif