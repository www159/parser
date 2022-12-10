#ifndef _W_DFA_H_
#define _W_DFA_H_
/**
 * 考虑关键字和标识符自动机的复杂性，构造一个regex还是有点必要的
 * 1.直接一个dfa一个函数即可
 * 2.自动机接受字符和读头指针，状态转移时读头指针跟着动。
 * 3.读头指针在移动时将会进行token的改写因此自动机需要维护一个token串
 * 
 * 4. 暂时支持代码自动机和数据结构自动机同时存在。
*/

typedef void (*hook)();
typedef void (*hook_token_gen)(char*, char*);
PUBLIC void null_hook(char* _, char* __);



/**
 * G(xfa_node, xfa_edge)
 * 邻接表的dfa
 * @struct xfa_node
 * 
*/
struct xfa_node {
    int end;                // 是否为终态
    hook_token_gen token_gen; // 终态需要一个特化的钩子函数来生成token
    struct xfa_edge* edge;
};



#define MAX_KEYWORD_SIZE    10
#define MAX_KEYWORD_CNT 50

struct keyword_index {
    char keyword[MAX_KEYWORD_SIZE];
    int type;
};


#define MAX_IDENTIFIER_SIZE 50
#define MAX_NUM_SIZE    50
#define MAX_STR_SIZE    1000

/**
 * dfa的边，为regex做铺垫
*/
#define LETTER  0
#define NUMBER  1
#define EPSILON 2
// #define CHAR    4
struct xfa_edge {
    int dfa_edge_type;
    char ch;
    struct xfa_node* next;
};

extern struct keyword_index keyword_table[MAX_KEYWORD_CNT];

#define dfa_node xfa_node
#define dfa_edge xfa_edge

PUBLIC void dfa_create(struct dfa_node* dfa);
/**
 * 递归删除
*/
PUBLIC void dfa_destroy(struct dfa_node* dfa);

/**
 * @brief 总dfa，读取一整个字符串，并生成一整串token
 * @param str 字符串
 * @param pin 读头指针
 * @param token 生成的token串
 * @return 0则没错
*/
PUBLIC int general_dfa(char* str, int* pin, char* token);

#endif