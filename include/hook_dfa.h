#ifndef _W_HOOK_DFA_H_
#define _W_HOOK_DFA_H_

PUBLIC void while_hook(char* token, char* _);
PUBLIC void for_hook(char* token, char* _);
PUBLIC void if_hook(char* token, char* _);
PUBLIC void else_hook(char* token, char* _);
PUBLIC void identifier_hook(char* token, char* name);

#endif