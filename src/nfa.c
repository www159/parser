#include <malloc.h>

#include "global.h"
#include "dfa.h"
#include "nfa.h"

PUBLIC void nfa_create(struct nfa_node* nfa) {
    nfa = (struct nfa_node*)malloc(sizeof(struct nfa_node));
}

/**
 * 递归删除
*/
PUBLIC void nfa_destroy(struct nfa_node* nfa) {
    if (nfa != NULL) free(nfa);
    /**
     * @todo
    */
}