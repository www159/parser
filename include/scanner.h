#ifndef _W_SCANNER_H_
#define _W_SCANNER_H_
/**
 * scanner，读头指针
 * 1. 读取文件并写入缓冲区，缓冲区空了再读，周而复始
 * 2. 最开始每次读取到界定符为止,唯一界定符为’
 * 
 * 3. symbol_table的生命周期：parser_init -> scanner完成所有工作
 * 是打印还是停留在内存中应该交给最上层的语法分析。因此要求symbol_table
 * 的内存释放在main函数中一定实现。调试阶段暂时交还给scanner
*/
#define BUFFER_SIZE 450
#define BUFFER_RESV 50
#define BUFFER_REAL_SIZE 500

PUBLIC void scanner_init();

PUBLIC void scan_file(FILE* fp);

#endif