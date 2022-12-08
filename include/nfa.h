#ifndef _W_NFA_H_
#define _W_NFA_H_

#define nfa_node xfa_node
#define nfa_edge xfa_edge

/**
 * 构造 e-nfa只有一个终态和一个初态的， 最后再消除e边
*/

PUBLIC void nfa_create(struct nfa_node* nfa);

PUBLIC void nfa_destroy(struct nfa_node* nfa);

PUBLIC void add_parallel_edge(struct nfa_node* nfa);

PUBLIC void add_serial_edge(struct nfa_node* nfa);

PUBLIC void add_positive_closure_edge(struct nfa_node* nfa);

PUBLIC void add_closure_edge(struct nfa_node* nfa);

#endif