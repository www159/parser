#include <stdio.h>

#include "global.h"
#include "scanner.h"

int main() {
    FILE* fp;
    fp = fopen("test_scanner.txt", "r");
    if (fp == NULL) {
        perror("failed to open file");
    }
    scan_file(fp);
    fclose(fp);
    return 0;
}