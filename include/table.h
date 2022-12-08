#ifndef _W_TABLE_H_
#define _W_TABLE_H_

// 符号类型
#define IMM 0
#define KEYWORD 1
#define OPERATOR 2
#define VAR 3
#define FUNCT 4

/**
 * @brief 关键字及其基本类型
 * 直接用define来构造一张无形的表(两个表项)
*/

//  关键字
#define WHILE 5
#define FOR 6
#define IF  7
#define ELSE    8

//  运算符
#define ASSIGN 38
#define ADD 9
#define MINUS   10
#define STAR    11
#define DIVIDE  12
#define LEFT_PAREN  13
#define RIGHT_PAREN 14 
#define AND 15
#define OR  16
#define NOT 17

//  条件运算符
#define EQU 18
#define N_EQU   19
#define LARGER  20
#define LESS    21
#define LARGER_EQU  22
#define LESS_EQU    23
#define C_AND   24
#define C_OR    25

// 界定符
#define SEMICOLON   26
#define LEFTBRACE   27
#define RIGHTBRACE  28

// 类型关键字
#define INT16   29
#define UINT16  30
#define INT32   31
#define INT 31
#define UINT32  32
#define UINT    32
#define INT64   33
#define UINT64  34
#define FLOAT32 35
#define FLOAT64 36
#define DOUBLE  36
#define STRING  37

//  
/**
 * 符号表
 * 接着符号表前三项分别是，立即数表索引，操作符表索引，关键字表索引
 * 三个其实可以共用一个数据结构
 * 向后增长的是变量，函数标识符
 */
PUBLIC struct token_location {
    int start_row;
    int start_col;
    int end_row;
    int end_col;
};

PUBLIC struct symbol_table_node {
    char name[200];
    int symbol_type;
    int type;
    struct token_location* addr;
    struct symbol_table_node* next;
};

// PUBLIC struct alias_table_node {
//     void* imm_ptr;
//     struct token_location* addr;
//     struct alias_table_node* next;
// };



PUBLIC void symbol_table_init();

PUBLIC void symbol_table_destroy();

PUBLIC void symbol_table_print();

// PUBLIC void alias_table_print();

/**
 * @brief 将标识符增加到符号表
 * @param name 标识符名称
 * @param symbol_type 标识符种类
 * @param type 如果标识符是变量，则有类型
 * @return 返回符号表位置
*/
PUBLIC int put_symbol_table(char* name, int symbol_type, struct token_location* location, int type);
/**
 * @brief 根据token获取相应的位置，报错用
 * @param token 形如"<TYPE，ADDR>"的字符串
 * @return 返回标识符的地址
*/
PUBLIC struct token_location* get_location(char* token);

#endif