#ifndef _W_REGEX_READER_H_
#define _W_REGEX_READER_H_

#define MAX_REGEX_READER_STR_SIZE MAX_REGEX_STR_SIZE
struct regex_reader {
    char str[MAX_REGEX_READER_STR_SIZE];
    int pin;
};

PUBLIC void regex_reader_create(char* str, struct regex_reader* reader);
PUBLIC void regex_reader_destroy(struct regex_reader* reader);
PUBLIC char next(struct regex_reader* reader);
PUBLIC char peek(struct regex_reader* reader);
PUBLIC int has_next(struct regex_reader* reader);
PUBLIC void str_in_paren(struct regex_reader* reader, char* str);
PUBLIC void str_to_next_parallel(struct regex_reader* reader, char* str);
#endif