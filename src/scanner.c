#include <stdio.h>
#include <string.h>

#include "global.h"
#include "scanner.h"
#include "parser.h"
#include "table.h"
#include "utils.h"

PRIVATE char file_buffer[BUFFER_SIZE + BUFFER_RESV];
PRIVATE int line;
PRIVATE int cur_pos;

PRIVATE void scanner_reset();

PUBLIC void scanner_init() {
    line = 0;
    cur_pos = 0;
    parser_init();
}

PUBLIC void scan_file(FILE* fp) {
    // scan_test(fp);
    while (!feof(fp)) {
        fgets(file_buffer, BUFFER_SIZE, fp);
        parse_str(file_buffer, line++);
    }

    /**
     * 一趟扫描结束，清空缓冲区
    */
    scanner_reset();
    /**
     * 符号表生命周期结束
    */
    symbol_table_destroy();   
}

PUBLIC void scan_and_write(FILE* dest, FILE* src) {
        // scan_test(fp);
    while (!feof(src)) {
        fgets(file_buffer, BUFFER_SIZE, src);
        parse_str(file_buffer, line++);
        parser_write(dest);
    }

    /**
     * 一趟扫描结束，清空缓冲区。
    */
    scanner_reset();
    
    /**
     * 符号表生命周期结束
    */
    symbol_table_destroy();   
}

PRIVATE void scan_test(FILE* fp) {
    fgets(file_buffer, BUFFER_SIZE, fp);
    printf("read str:\n%s\n, size is:\n%ld\n, last ch is:\n%c\n", file_buffer, strlen(file_buffer), file_buffer[4]);
}

PRIVATE void scanner_reset() {
    line = 0;
    cur_pos = 0;
    strclr(file_buffer);
}

