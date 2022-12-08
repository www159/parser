#ifndef _W_REGEX_H_
#define _W_REGEX_H_

/**
 * @deprecated
 * 正规表达式，一个字符串，能够抽象三型语言
 * regex -> e-nfa -> nfa -> dfa -> mdfa
 * 具体流程: 
 * 1.根据基本正则语法构造出基本自动机nfa，比如数字，关键字等等。
 * 2.根据文法，将基本自动机nfa进行拼接，合并，闭包等等得到一个
 * 终极e-nfa
 * 3.化简终极e-nfa得到终极m-dfa,最终会用这个终极m-dfa进行词法
 * 分析
 * 4.注意到每个基本自动机的所有终态将会触发钩子函数进行符号表的
 * 相关操作。
 * 5.在进行nfa的拼接时，终态会重置，因此钩子函数会扩散到中间态中
*/

/**
 * 正规表达式类，包含正规语句字符，以及一个m-dfa的起点
*/
// struct regular_expr {
//     char str[200];
//     struct dfa mdfa;
// }


#endif