#ifndef _W_UTILS_H_
#define _W_UTILS_H_

PUBLIC void strclr(char* str);

PUBLIC void strapd(char* str, char ch);

PUBLIC void strsub(char* dest, const char* src, size_t pos, size_t len);

#define MAX(a, b) ((a < b) ? (b) : (a))

PUBLIC void strswp(char* a, char* b);

PUBLIC int isescape(char ch);

/**
 * @brief 将字符串内的转义字符串转换为字符串变量
 * @param dest 字符串
 * @param src 转义字符串
*/
PUBLIC int escape2str(char* dest, const char* src);

#endif