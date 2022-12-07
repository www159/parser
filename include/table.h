#ifndef _W_TABLE_H_
#define _W_TABLE_H_

// 符号类型
#define VAR 0
#define IMM 1
#define KEYWORD 2
#define OPERATOR 3
#define FUNCT 4

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
    char type[20];
    struct token_location* addr;
    struct symbol_table_node* next;
};

PUBLIC struct alias_table_node {
    void* imm_ptr;
    struct token_location* addr;
    struct alias_table_node* next;
};



PUBLIC void symbol_table_init();

PUBLIC void symbol_table_destroy();

PUBLIC void symbol_table_print();

PUBLIC void alias_table_print();

/**
 * @brief 将标识符增加到符号表
 * @param name 标识符名称
 * @param symbol_type 标识符种类
 * @param type 如果标识符是变量，则有类型
 * @param token 生成的token
*/
PUBLIC void put_symbol_table(char* name, int symbol_type, struct token_location* location, char* type, char* token);
/**
 * @brief 根据token获取相应的值
 * @param token 形如"<TYPE，ADDR>"的字符串
 * @return 返回标识符的地址
*/
PUBLIC struct token_location* get_location(char* token);

#endif