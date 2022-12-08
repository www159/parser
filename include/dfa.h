#ifndef _W_DFA_H_
#define _W_DFA_H_
/**
 * 考虑到编译器的特殊性，在编译器内部实现regex有点臃肿。
 * 1.直接一个dfa一个函数即可
 * 2.自动机接受字符和读头指针，状态转移时读头指针跟着动。
 * 3.读头指针在移动时将会进行token的改写因此自动机需要维护一个token串
*/

/**
 * @brief 总dfa，读取一整个字符串，并生成一整串token
 * @param str 字符串
 * @param pin 读头指针
 * @param token 生成的token串
 * @return 0则没错
*/
PUBLIC int general_dfa(char* str, int* pin, char* token);

#endif