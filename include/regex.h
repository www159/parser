#ifndef _W_REGEX_H_
#define _W_REGEX_H_

/**
 * @deprecated
 * 正规表达式，一个字符串，能够抽象三型语言
 * regex -> e-nfa -> nfa -> dfa -> mdfa
 * 1.注意到不同的关键字有不同的钩子函数，因
 * 2.考虑到钩子函数的特化需要调用regex相关
*/

#define MAX_REGEX_STR_SIZE 200
/**
 * @struct 正规表达式类，包含正规语句字符，以及一个m-dfa的起点
*/
struct regular_expr {
    char str[MAX_REGEX_STR_SIZE];
    struct dfa_node* dfa;
    struct nfa_node* nfa;
};

/**
 * @brief 通过regex字符串生成regex，包含dfa和nfa
 * @param regex_str regex字符串
 * @param regex regex对象
*/
PUBLIC void regex_create(char* regex_str, struct regular_expr* regex);
PUBLIC void regex_destroy(struct regular_expr* regex);
PUBLIC void regex_create_with_hook(char* regex, ...);
PUBLIC int regex_match(char* regex);
PUBLIC int regex_match_s(char* regex, char* str, int* pin, char* token);
#endif