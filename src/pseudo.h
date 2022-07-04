/*
 *      pseudo --- pseudo op processing
 */

#ifndef PSEUDO_H
#define PSEUDO_H

extern struct oper pseudo[];

int sizeof_pseudo();
void do_pseudo(int op /* which op */);

#endif // PSEUDO_H
