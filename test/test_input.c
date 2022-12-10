#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;

#include "global.h"
#include "scanner.h"




/**
 * wwc, wtoolschain w compile.
 * 类似gcc的用法
 * -m 获取中间代码代码。    -m dest src
 * 
 * @attention 暂时使用getopt，之后自己实现一个
*/
#define MAX_FILE_PATH 100

const char* optstring = "am:";

PRIVATE void usage() {
    return;
}

/**
 * @brief 识别目标中间代码文件和源码文件，并进行文件操作
 * @param file_path_str 文件路径集合，如果文件数超过两
 * 个，则取前两个
*/
PRIVATE void middle_parse(char* files_path_str) {
    char *token, *dest, *src;
    char* split = " ";
    int cnt = 0;

    token = strtok(files_path_str, split);
    while (token != NULL) {
        cnt++;
        printf("file path is:%s\n", token);
        if (cnt == 1) {
            dest = token;
        }
        else if (cnt == 2) {
            src = token;
        }
        else {
            break;
        }
        token = strtok(NULL, split);
    }
    if(cnt < 2) {
        printf("缺少源文件: %s\n", files_path_str);
        exit(1);
    } 
    // printf("目标路径:%s\n源码路径:%s\n", dest, src);
}

PUBLIC int main(int argc, char** argv) {
    int arg;
    
    printf("program start\n");
    while ((arg = getopt(argc, argv, optstring)) != -1) {
        // printf("args: %c\n", arg);
        switch (arg) {
            case 'm': 
                printf("parse start\n");
                printf("全部文件: %s\n", optarg);
                middle_parse(optarg);
                printf("parse done!\n");
                break;
            case '?':
                printf("格式错误");
                usage();
                break;
        }
    }
    printf("program done!\n");
    return 0;
}

// PUBLIC int main(int argc, char *argv[]) {
//     int o;
//     const char *optstring = "abc::"; // 有三个选项-abc，其中c选项后有两个冒号，表示后面可选参数
//     while ((o = getopt(argc, argv, optstring)) != -1) {
//         switch (o) {
//             case 'a':
//                 printf("opt is a, oprarg is: %s\n", optarg);
//                 break;
//             case 'b':
//                 printf("opt is b, oprarg is: %s\n", optarg);
//                 break;
//             case 'c':
//                 printf("opt is c, oprarg is: %s\n", optarg);
//                 break;
//             case '?':
//                 printf("发生错误时提示用户正确的使用方式\n");
//                 usage(); // 提示使用说明
//                 break;
//         }
//     }
//     return 0;
// }