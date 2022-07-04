/*
 *      install --- add a symbol to the table
 */

#ifndef SYMTAB_H
#define SYMTAB_H

int install(char *str, int val);
struct nlist *lookup(char *name);
struct oper *mne_look(char *str);

#endif // SYMTAB_H
