#include <string.h>

#include "global.h"
#include "utils.h"

PUBLIC void strclr(char* str) {
    str[0] = '\0';
}

PUBLIC void strapd(char* str, char ch) {
    char s[2];
    s[0] = ch;
    s[1] = '\0';

    strcat(str, s);
}

PUBLIC void strsub(char* dest, const char* src, size_t pos, size_t len) {
    size_t p = 0;
    for (size_t i = pos; i < pos + len; i++) {
        dest[p++] = src[i];
    }
    dest[p] = '\0';
}

PUBLIC void strswp(char* a, char* b) {
    size_t la = strlen(a);
    size_t lb = strlen(b);
    size_t lmax = MAX(la, lb);
    for (size_t i = 0; i < lmax; i++) {
        char t = a[i];
        a[i] = b[i];
        b[i] = t;
    }
}

PUBLIC int isescape(char ch) {
    switch (ch) {
        case '\"':
        case '\'':
        case '\\':
        case 'n':
        case 'r':
        case 't':
            return 1;
            break;
        default: 
            return 0;
            break;
    }
    return 0;
}

PUBLIC int escape2str(char* dest, const char* src) {
    int ls = strlen(src);
    int ps = 0;
    int pd = 0;

    int state = 0;
    while (ps < ls) {
        switch (state) {
            case 0:
                switch (src[ps]) {
                    case '\\':
                        state = 1;
                        break;
                    case '\"':
                    case '\'':
                        break;
                    default:
                        dest[pd++] = src[ps];
                        break;
                }
                ps++;
                break;
            case 1:
                switch (src[ps]) {
                    case 'n': 
                        state = 0;
                        dest[pd++] = '\n';
                        break;
                    case 'r':
                        state = 0;
                        dest[pd++] = '\r';
                        break;
                    case 't':
                        state = 0;
                        dest[pd++] = '\t';
                        break;
                    case '\"':
                        state = 0;
                        dest[pd++] = '\"';
                        break;
                    case '\'':
                        state = 0;
                        dest[pd++] = '\'';
                        break;
                    case '\\':
                        state = 0;
                        dest[pd++] = '\\';
                        break;
                    default: 
                        return 1;
                        break;
                }
                ps++;
                break;
        }
    }
}