#include <malloc.h>
#include <string.h>

#include "global.h"
#include "table.h"
#include "dfa.h"
#include "nfa.h"
#include "regex.h"
#include "regex_reader.h"


PRIVATE struct regex_reader* reader;
PRIVATE void regex2nfa(struct nfa_node* nfa);

PUBLIC void regex_create(char* regex_str, struct regular_expr* regex) {
    regex = (struct regular_expr*)malloc(sizeof(struct regular_expr));
    strcpy(regex->str, regex_str);

    /**
     * regex -> e-nfa
    */
    nfa_create(regex->nfa);
    regex_reader_create(regex_str, reader);
    regex2nfa(regex->nfa);
    regex_reader_destroy(reader);
    dfa_create(regex->dfa);
}

PUBLIC void regex_destroy(struct regular_expr* regex) {
    nfa_destroy(regex->nfa);
    dfa_destroy(regex->dfa);
    if (regex != NULL){
        free(regex);
    }
}

PRIVATE void regex2nfa(struct nfa_node* nfa) {
    return;
}
