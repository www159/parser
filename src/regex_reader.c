#include <malloc.h>
#include <string.h>

#include "global.h"
#include "regex.h"
#include "regex_reader.h"

PUBLIC void regex_reader_create(char* str, struct regex_reader* reader) {
    reader = (struct regex_reader*)malloc(sizeof(struct regex_reader));
    strcpy(reader->str, str);
    reader->pin = 0;
}

PUBLIC void regex_reader_destroy(struct regex_reader* reader) {
    if (reader != NULL) {
        free(reader);
    }
}