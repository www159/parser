#ifndef _W_TABLE_H_
#define _W_TABLE_H_

enum CONST_TABLE {
    /**
     * 符号类型, 5, 5
    */
    IMM, KEYWORD, OPERATOR, VAR, FUNCT,
    /**
     * 关键字, 4, 9
    */
    WHILE, FOR, IF, ELSE,
    /**
     * 运算符, 11, 20
    */
    ASSIGN, ADD, MINUS, STAR, DIVIDE ,MOD, LEFT_PAREN, RIGHT_PAREN,
    AND, OR, NOT,
    /**
     * 条件运算符, 9, 29
    */
    EQU, N_EQU, LARGER, LESS, LARGER_EQU, LESS_EQU, C_AND, C_OR, C_NOT,
    /**
     * 三目运算符
    */
    COLON,
    /**
     * 界定符, 4, 33
    */
    SEMICOLON, SINGLE_QUOTE, LEFT_BRACE, RIGHT_BRACE,
    /**
     * 类型关键字, 9, 42
    */
    INT16, UINT16, INT32, UINT32, INT64, UINT64, FLOAT32, FLOAT64, STRING,
    CHAR,
    /**
     * 无效关键字, 1, 43
    */
    NULL_CONST_NODE
    /**
     * 编译无关关键字, 1, 44
    */
};
/**
 * @brief 关键字及其基本类型
 * 直接用define来构造一张无形的表(两个表项)
*/

#define INT INT32
#define UINT UINT32
#define FLOAT FLOAT32
#define DOUBLE FLOAT64
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