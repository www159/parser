#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"
#include "utils.h"

#define ln printf("\n");

int main() {
    printf("test utils");ln

    char s1[500] = "12345";
    char s2[500] = "12345";
    char s3[] = "";

    printf("test strclr()");ln
    printf("%s", s1);ln
    strclr(s1);
    printf("it should be none:%s", s1);ln
    // if (!strcmp(s1, s3)) {
    //     printf("error");ln
    //     exit(1);
    // }
    ln
    
    // printf("test strapd()");ln
    // strcpy(s1, s2);
    // return 0;

    printf("test escape2str()");ln
    strcpy(s1, "\"ab\\n\\\"c\\\" \'d\' efh\"");
    printf("raw str is: %s", s1);ln
    escape2str(s2, s1);
    printf("origin str is: %s", s2);ln
}