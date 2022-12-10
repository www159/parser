#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "token.h"
#include "table.h"
#include "dfa.h"
#include "utils.h"

PUBLIC struct keyword_index keyword_table[MAX_KEYWORD_CNT] = {
    {"while",   WHILE},
    {"for", FOR},
    {"if",  IF},
    {"else",    ELSE},
    {"int16",   INT64},
    {"uint16",  UINT16},
    {"int32",   INT32},
    {"uint32",  UINT32},
    {"int64",   INT64},
    {"uint64",  UINT64},
    {"int", INT},
    {"uint",    UINT},
    {"float32", FLOAT32},
    {"float",   FLOAT},
    {"float64", FLOAT64},
    {"double", DOUBLE},
    {"string", STRING}
};

/**
 * @brief 数字自动机
 * @param str 符号串
 * @param pin 读头指针
 * @param token 生成的token串
*/
PRIVATE int digit_dfa(char* str, int* pin, char* token);

/**
 * @brief 字母自动机，或标识符自动机
 * @param str 符号串
 * @param pin 读头指针
 * @param token 生成的token串
*/
PRIVATE int alpha_dfa(char* str, int* pin, char* token);

/**
 * @brief 其他符号自动机
 * @param str 符号串
 * @param pin 读头指针
 * @param token 生成的token串
*/
PRIVATE int other_dfa(char* str, int* pin, char* token);

/**
 * @brief 关键字自动机
 * @param str 符号串
 * @param pin 读头指针
 * @param token 生成的token串
*/
PRIVATE int keyword_dfa(char* str, int* pin, char* token);

/**
 * @brief 字符串自动机
 * @param str 符号串
 * @param pin 读头指针
 * @param token 生成的token串
*/
PRIVATE int str_ch_dfa(char* str, int* pin, char* token);
/**
 * @brief 去掉token串中最后一个token
 * @param token token串
*/
PRIVATE void remove_last_token(char* token);

PUBLIC void null_hook(char* _, char* __) {
    return;
}

PUBLIC void dfa_create(struct dfa_node* dfa) {
    dfa = (struct dfa_node*)malloc(sizeof(struct dfa_node));
}

/**
 * 递归删除
*/
PUBLIC void dfa_destroy(struct dfa_node* dfa) {
    /**
     * @todo
    */
    if (dfa != NULL) free(dfa);
}

/**
 * 需要加入一点不确定性
*/
PUBLIC int general_dfa(char* str, int* pin, char* token) {
    int stop = 0;
    int state = 0;
    int err = 0;

    while (!stop && str[*pin] != '\0') {
        switch (state) {
            case 0:
                if (isdigit(str[*pin])) {
                    /**
                     * 如果为数字，进入数字自动机
                    */
                    err = digit_dfa(str, pin, token);
                }
                else if (isalpha(str[*pin])) { 
                    
                    /**
                     * 如果为字母
                     * 1. 先进入关键字自动机
                     * 
                     * 2. 如果关键字自动机到达终态，并不会
                     * 生成token串，而是继续扫描，判断是否
                     * 进入字母表自动机，否则生成token，是
                     * 则读头指针重置为初始位置，进入字母表
                     * 自动机
                     * 
                     * 3. 如果关键字自动机失配，同样继续扫
                     * 描，判断是否进入字母表自动机
                    */

                    int begin;
                    
                    /**
                     * 记住初始位置
                    */
                    begin = *pin;
                    err = keyword_dfa(str, pin, token);

                    if (err) {
                        /**
                         * 如果在关键字自动机中失配
                        */
                        char u;

                        u = str[*pin];
                        if (isalpha(u) || isdigit(u) || u == '_') {
                            /**
                             * 能够进入字母自动机
                            */
                            *pin = begin;
                            err = alpha_dfa(str, pin, token);   
                        }
                        else {
                            /**
                             * 不能进入字母自动机
                             * 抛出错误
                            */
                           return err;
                        }
                    }
                    else {
                        /**
                         * 如果在关键字自动机中匹配
                        */
                       char u;

                       u = str[*pin];
                       if (isalpha(u) || isdigit(u) || u == '_') {
                            *pin = begin;
                            remove_last_token(token);
                            err = alpha_dfa(str, pin, token);
                       }
                       else {
                            /**
                             * 如果不能进入字母表自动机，生成token
                            */
                       }
                    }
                }
                else if (str[*pin] == '\"' || str[*pin] == '\'') {
                    /**
                     * 字符常量自动机
                    */
                    err = str_ch_dfa(str, pin, token);
                }
                else {  // 其他字符，进入其他字符自动机
                    err = other_dfa(str, pin, token);
                }
                if (err) {
                    // 在子自动机的中间态终止
                    return 1;
                }
                // (*pin)++;
                break;
        }
    }
    return 0;
}

PRIVATE int digit_dfa(char* str, int* pin, char* token) {
    int stop = 0;
    int state = 0;
    int type = NULL_CONST_NODE;
    int begin = *pin;
    char num[MAX_NUM_SIZE];

    strclr(num);
    while (!stop) {
        switch (state) {
            case 0:
                if (isdigit(str[*pin])) {
                    state = 0;
                    type = INT;
                    (*pin)++;
                }
                else if (str[*pin] == '.') {
                    state = 1;
                    (*pin)++;
                }
                else {
                    stop = 1;
                    strsub(num, str, begin, *pin - begin);
                    set_token(token, IMM, type, num);
                }
                break;
            case 1:
                if (isdigit(str[*pin])) {
                    state = 2;
                    type = FLOAT;
                    (*pin)++;
                }
                else {
                    return 1;
                }
                break;
            case 2:
                 if (isdigit(str[*pin])) {
                    state = 2;
                    (*pin)++;
                 }
                 else {
                    stop = 1;
                    strsub(num, str, begin, *pin - begin);
                    set_token(token, IMM, type, num);
                 }
                 break;
        }
    }

    return 0;
}

PRIVATE int alpha_dfa(char* str, int *pin, char* token) {
    int state = 0;
    int stop = 0;
    int begin = *pin;
    char identifier[MAX_IDENTIFIER_SIZE];

    strclr(identifier);
    while (!stop) {
        switch (state) {
            case 0:
                if (isalpha(str[*pin]) || str[*pin] == '_') {
                    state = 1;
                    (*pin)++;
                }
                else {
                    return 1;
                }
                break;
            case 1:
                if (isalpha(str[*pin]) || isdigit(str[*pin]) || str[*pin] == '_') {
                    state = 1;
                    (*pin)++;
                }
                else {
                    stop = 1;
                    strsub(identifier, str, begin, *pin - begin);
                    set_token(token, VAR, NULL_INT, identifier);
                }
                break;
        }
    }
    return 0;
}

PRIVATE int other_dfa(char* str, int *pin, char* token) {
    int stop = 0;
    int state = 0;
    int type = NULL_CONST_NODE;

    while (!stop) {
        switch (state) {
            /**
             * 0号状态，可以是终态
            */
            case 0:
                switch(str[*pin]) {
                    case '\r':
                    case '\n':
                    case ' ':
                    case '\t':
                    case '\v':
                        stop = 1;
                        break;
                    case '+':
                        type = ADD;
                        // set_token(token, OPERATOR, ADD, NULL);
                        state = 4;
                        break;
                    case '-':
                        type = MINUS;
                        // set_token(token, OPERATOR, MINUS, NULL);
                        state = 4;
                        break;
                    case '*':
                        type = STAR;
                        state = 4;
                        break;
                    case '/':
                        type = DIVIDE;
                        // set_token(token, OPERATOR, DIVIDE, NULL);
                        state = 4;
                        break;
                    case '%':
                        type = MOD;
                        // set_token(token, OPERATOR, MOD, NULL);
                        state = 4;
                        break;
                    /**
                     * @todo 条件运算符
                    */
                    case '&':
                        type = AND;
                        state = 1;
                        break;
                    case '|':
                        type = OR;
                        // set_token(token, OPERATOR, OR, NULL);
                        state = 2;
                        break;
                    case '~':
                        type = NOT;
                        // set_token(token, OPERATOR, NOT, NULL);
                        stop = 1;
                        break;
                    case '>':
                        state = 3;
                        type = LARGER;
                        break;
                    case '<':
                        state = 3;
                        type = LESS;
                        break;
                    case '=':
                        state = 3;
                        type = ASSIGN;
                        break;
                    case '!':
                        state = 3;
                        type = C_NOT;
                        break;
                    /**
                     * 三目运算符
                    */
                    case ':':
                        type = COLON;
                        state = 4;
                        break;
                    /**
                     * 界定符
                    */
                    case ';':
                        type = SEMICOLON;
                        state = 4;
                        break;
                    default:
                        if (type == NULL_CONST_NODE) return -1;
                        set_token(token, OPERATOR, type, NULL);
                        stop = 1;
                        (*pin)--;
                        break;
                }
                (*pin)++;
                break;
            case 1:
                switch (str[*pin]) {
                    case '&':
                        state = 4;
                        type = C_AND;
                        break;
                    default:
                        set_token(token, OPERATOR, AND, NULL);
                        stop = 1;
                        (*pin)--;
                        break;
                }
                (*pin)++;
                break;
            case 2:
                switch (str[*pin]) {
                    case '|':
                        state = 4;
                        type = C_OR;
                        break;
                    default:
                        set_token(token, OPERATOR, OR, NULL);
                        stop = 1;
                        (*pin)--;
                        break;
                }
                (*pin)++;
                break;
            case 3:
                switch (str[*pin]) {
                    case '=':
                        switch (type) {
                            case ASSIGN:
                                type = EQU;
                                break;
                            case LARGER:
                                type = LARGER_EQU;
                                break;
                            case LESS:
                                type = LESS_EQU;
                                break;
                            case C_NOT:
                                type = N_EQU;
                                break;
                            default:
                                return 1;
                                break;
                        }
                        state = 4;
                        break;
                    default:
                        set_token(token, OPERATOR, type, NULL);
                        stop = 1;
                        (*pin)--;
                        break;
                }
                (*pin)++;
                break;
            case 4:
                set_token(token, OPERATOR, type, NULL);
                stop = 1;
                break;
        }
    }

    return 0;
}

/**
 * @todo ac自动机实现
 * 如今暂时使用最蠢的strcpy
*/
PRIVATE int keyword_dfa(char* str, int* pin, char* token) {
    int p = 0;
    int len;

    while (p < MAX_KEYWORD_CNT && ((len = strlen(keyword_table[p].keyword)) != 0))
    {
        int i;
        int begin = *pin;

        for (i = 0; i < len; i++) {
            if (str[*pin] == keyword_table[p].keyword[i]) {
                (*pin)++;
            }
            else {
                *pin = begin;
                break;
            }
        }
        
        if (i == len) {
            set_token(token, KEYWORD, keyword_table[p].type, NULL);
            return 0;
        }
        p++;
    }
    return 1;
}

PRIVATE int str_ch_dfa(char* str, int* pin, char* token) {
    int stop = 0;
    int state = 0;
    int type = NULL_CONST_NODE;
    int begin = *pin;
    char str_ch[MAX_STR_SIZE];
    char raw_str[MAX_STR_SIZE];

    strclr(str_ch);
    strclr(raw_str);
    while (!stop) {
        switch (state) {
            case 0:
                switch (str[*pin])
                {
                    case '\"':
                        state = 1;
                        type = STRING;
                        (*pin)++;
                        break;
                    case '\'':
                        state = 2;
                        type = CHAR;
                        (*pin)++;
                        break;
                    default:
                        return 1;
                }
                break;
            case 1:
                switch (str[*pin])
                {
                    case '\\':
                        state = 3;
                        break;
                    case '\"':
                        state = 4;
                        break;
                    default:
                        state = 1;
                        break;
                }
                (*pin)++;
                break;
            case 2:
                switch (str[*pin]) {
                    case '\\':
                        state = 5;
                        break;
                    case '\'':
                        /**
                         * 空字符不存在
                        */
                        return 1;
                        break;
                    default:
                        state = 6;
                        break;
                }
                (*pin)++;
                break;
            case 3:
                if (isescape(str[*pin])) {
                    state = 1;
                    (*pin)++;
                }
                else {
                    return 1;
                }
                break;
            case 4:
                stop = 1;
                strsub(raw_str, str, begin, *pin - begin);
                escape2str(str_ch, raw_str);
                set_token(token, IMM, STRING, str_ch);
                break;
            case 5:
                if (isescape(str[*pin])) {
                    state = 6;
                    (*pin)++;
                }
                else {
                    return 1;
                }
                break;
            case 6:
                if (str[*pin] == '\'') {
                    stop = 1;
                    strsub(raw_str, str, begin, *pin - begin);
                    escape2str(str_ch, raw_str);
                    set_token(token, IMM, CHAR, str_ch);
                }
                else {
                    /**
                     * 字符长度永远为1
                    */
                    return 1;
                }
                break;
        }
    }
    
}
/**
 * 工具函数
*/
PRIVATE void remove_last_token(char* token) {
    size_t len;
    
    len = strlen(token);
    while (token[len - 1] != '<' && len) {
        len--;
    }

    token[len - 1] = '\0';
}

// PRIVATE void is_not_escape(char ch) {
//     switch (ch) {
//         case '\\':
//         case '\"':
//         case 
//     }
// }