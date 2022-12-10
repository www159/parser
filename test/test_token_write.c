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
const char* MIDDLE_FILE_SUFFIX = ".m";
const char* optstring = "am:";

PRIVATE char default_dest[MAX_FILE_PATH];
PRIVATE void usage();
PRIVATE void default_mid_path(char* dest, char* src);

/**
 * @brief 识别目标中间代码文件和源码文件，并进行文件操作
 * @param file_path_str 文件路径集合
*/
PRIVATE void middle_parse(char* files_path_str) {
    char *token, *dest, *src;
    char* split = " ";
    int cnt = 0;
    FILE *dest_fp, *src_fp;

    /**
     * 获取到目标路径和源路径
     * 1.如果路径只有一个，则生成目标默认
     * 路径，即在源文件名加上.m的后缀。
     * 2.如果路径有两个，则为[dest, src]
    */
    token = strtok(files_path_str, split);
    while (token != NULL) {
        cnt++;
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
    

    /**
     * 只有一个路径，生成默认目标路径
    */
   if (cnt == 1) {
        src = dest;
        dest = default_dest;
        default_mid_path(dest, src);
   }

   /**
    * 文件读写操作
   */
    dest_fp = fopen(dest, "w");
    src_fp = fopen(src, "r");
    scan_and_write(dest_fp, src_fp);

    fclose(dest_fp);
    fclose(src_fp);
}

PUBLIC int main(int argc, char** argv) {
    int arg;

    /**
     * 初始化工作
    */
    scanner_init();

    printf("start\n");
    while ((arg = getopt(argc, argv, optstring)) != -1) {
        // printf("args: %c\n", arg);
        switch (arg) {
            case 'm': 
                printf("parse start\n");
                middle_parse(optarg);
                break;
            case '?':
                printf("格式错误");
                usage();
                break;
        }
    }
    return 0;
}

PRIVATE void usage() {
    return;
}

PRIVATE void default_mid_path(char* dest, char* src) {
    strcpy(dest, src);
    strcat(dest, MIDDLE_FILE_SUFFIX);
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