#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "dfa.h"
#include "token.h"
#include "table.h"

PRIVATE int digit_dfa(char* str, int* pin, char* token);
PRIVATE int alpha_dfa(char* str, int* pin, char* token);
PRIVATE int other_dfa(char* str, int* pin, char* token);

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

PUBLIC int general_dfa(char* str, int* pin, char* token) {
    int stop = 0;
    int state = 0;
    int err = 0;

    while (!stop || str[*pin] != '\0') {
        switch (state) {
            case 0:
                if (isdigit(str[*pin])) {// 如果为数字，进入数字自动机
                    err = digit_dfa(str, pin, token);
                }
                else if (isalpha(str[*pin])) { // 如果为字母，进入字母自动机
                    err = alpha_dfa(str, pin, token);
                }
                else {  // 其他字符，进入其他字符自动机
                    err = other_dfa(str, pin, token);
                }
                if (err) {
                    return 1;
                }
                (*pin)++;
                break;
        }
    }
    return 0;
}

PUBLIC void error(char* msg) {
    printf(msg);
    exit(1);
}

PRIVATE int digit_dfa(char* str, int* pin, char* token) {
    int stop = 0;
    int state = 0;

    while (!stop) {

    }

    return 0;
}

PRIVATE int alpha_dfa(char* str, int *pin, char* token) {
    return 0;
}

PRIVATE int other_dfa(char* str, int *pin, char* token) {
    int stop = 0;
    int state = 0;
    while (!stop) {
        switch (state) {
            /**
             * 0号状态，可以是终态
            */
            case 0:
                switch(str[*pin]) {
                    case '+':
                        set_token(token, OPERATOR, ADD, NULL);
                        stop = 1;
                        break;
                    case '-':
                        set_token(token, OPERATOR, MINUS, NULL);
                        stop = 1;
                        break;
                    case '*':
                        set_token(token, OPERATOR, STAR, NULL);
                        stop = 1;
                        break;
                    case '/':
                        set_token(token, OPERATOR, DIVIDE, NULL);
                        stop = 1;
                        break;
                    /**
                     * @todo 条件运算符
                    */
                    case '&':
                        set_token(token, OPERATOR, AND, NULL);
                        stop = 1;
                        break;
                    case '|':
                        set_token(token, OPERATOR, OR, NULL);
                        stop = 1;
                        break;
                    case '~':
                        set_token(token, OPERATOR, NOT, NULL);
                        stop = 1;
                        break;
                    // case '!':
                    // case '=':
                    default:
                        return 1;
                        // 不可达代码
                        stop = 1;
                        break;
                }
        }
    }

    return 0;
}