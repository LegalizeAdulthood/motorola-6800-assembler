/*
 *	MC6800/02 specific processing
 */

#ifndef DO_H
#define DO_H

void localinit();
void do_op(int opcode /* base opcode */, int opClass /* mnemonic class */);

#endif // DO_H
