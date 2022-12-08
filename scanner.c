#include <stdio.h>
#include <string.h>

#include "global.h"
#include "scanner.h"
#include "parser.h"
#include "table.h"

PRIVATE char file_buffer[BUFFER_SIZE + BUFFER_RESV];
PRIVATE int line;
PRIVATE int cur_pos;

PUBLIC void scanner_init() {
    line = 0;
    cur_pos = 0;
    parser_init();
}

// 扫描文件并进行parser
PUBLIC void scan_file(FILE* fp) {
    // scan_test(fp);
    while (!feof(fp)) {
        fgets(file_buffer, BUFFER_SIZE, fp);
        parse_str(file_buffer, line++);
    }

    // 符号表生命周期结束
    symbol_table_destroy();   
}

PRIVATE void scan_test(FILE* fp) {
    fgets(file_buffer, BUFFER_SIZE, fp);
    printf("read str:\n%s\n, size is:\n%ld\n, last ch is:\n%c\n", file_buffer, strlen(file_buffer), file_buffer[4]);
}

