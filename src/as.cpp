#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "as.h"
#include "do.h"
#include "ffwd.h"
#include "globals.h"
#include "output.h"
#include "pseudo.h"
#include "symtab.h"
#include "util.h"

void initialize();
void make_pass();
void re_init();
void process();
int parse_line();

/*
        as ---	cross assembler main program
 */
int main(int argc, char *argv[])
{
    char **np;
    char *i;
    int j = 0;

    if (argc < 2)
    {
        printf("Usage: %s <files> [-options]\n"
            "Options:\n"
            "l       Produce a listing\n"
            "nol     Do not produce a listing\n"
            "c       Print cycle counts in listing\n"
            "noc     Do not print cycle counts in listing\n"
            "s       Produce a symbol table\n"
            "cre     Produce a symbol cross reference table\n", argv[j]);
        exit(1);
    }
    Argv = argv;
    initialize();
    while ((*argv[j] != '-') && (j < argc))
    {
        j++;
        if (j == argc)
            break;
    }
    N_files = j - 1;
    if (j < argc)
    {
        argv[j]++;
        while (j < argc)
        {
            for (i = argv[j]; *i != 0; i++)
                if ((*i <= 'Z') && (*i >= 'A'))
                    *i = *i + 32;
            if (strcmp(argv[j], "l") == 0)
                Lflag = 1;
            else if (strcmp(argv[j], "nol") == 0)
                Lflag = 0;
            else if (strcmp(argv[j], "c") == 0)
                Cflag = 1;
            else if (strcmp(argv[j], "noc") == 0)
                Cflag = 0;
            else if (strcmp(argv[j], "s") == 0)
                Sflag = 1;
            else if (strcmp(argv[j], "cre") == 0)
                CREflag = 1;
            j++;
        }
    }
    root = nullptr;

    Cfn = 0;
    np = argv;
    Line_num = 0; /* reset line number */
    while (++Cfn <= N_files)
        if ((Fd = fopen(*++np, "r")) == nullptr)
            printf("as: can't open %s\n", *np);
        else
        {
            make_pass();
            fclose(Fd);
        }
    if (Err_count == 0)
    {
        Pass++;
        re_init();
        Cfn = 0;
        np = argv;
        Line_num = 0;
        while (++Cfn <= N_files)
            if ((Fd = fopen(*++np, "r")) != nullptr)
            {
                make_pass();
                fclose(Fd);
            }
        if (Sflag == 1)
        {
            printf("\f");
            stable(root);
        }
        if (CREflag == 1)
        {
            printf("\f");
            cross(root);
        }
        fprintf(Objfil, "S9030000FC\n"); /* at least give a decent ending */
    }
    exit(Err_count);
}

void initialize()
{
    int i = 0;

#ifdef DEBUG
    printf("Initializing\n");
#endif
    Err_count = 0;
    Pc = 0;
    Pass = 1;
    Lflag = 0;
    Cflag = 0;
    Ctotal = 0;
    Sflag = 0;
    CREflag = 0;
    N_page = 0;
    Line[MAXBUF - 1] = NEWLINE;

    std::string Obj_name = Argv[1]; /* copy first file name into array */
    auto pos = Obj_name.find_last_of(".");
    if (pos != std::string::npos)
        Obj_name.erase(pos);
    Obj_name += ".s19";
    if ((Objfil = fopen(Obj_name.c_str(), "w")) == nullptr)
        fatal("Can't create object file");
    fwdinit();   /* forward ref init */
    localinit(); /* target machine specific init. */
}

void re_init()
{
#ifdef DEBUG
    printf("Reinitializing\n");
#endif
    Pc = 0;
    E_total = 0;
    P_total = 0;
    Ctotal = 0;
    N_page = 0;
    fwdreinit();
}

void make_pass()
{
#ifdef DEBUG
    printf("Pass %d\n", Pass);
#endif
    while (fgets(Line, MAXBUF - 1, Fd) != (char *)nullptr)
    {
        Line_num++;
        P_force = 0; /* No force unless bytes emitted */
        N_page = 0;
        if (parse_line())
            process();
        if (Pass == 2 && Lflag && !N_page)
            print_line();
        P_total = 0; /* reset byte count */
        Cycles = 0;  /* and per instruction cycle count */
    }
    f_record();
}

/*
 *	parse_line --- split input line into label, op and operand
 */
int parse_line()
{
    register char *ptrfrm = Line;
    register char *ptrto = Label;

    if (*ptrfrm == '*' || *ptrfrm == '\n')
        return (0); /* a comment line */

    while (delim(*ptrfrm) == NO)
        *ptrto++ = *ptrfrm++;
    if (*--ptrto != ':')
        ptrto++; /* allow trailing : */
    *ptrto = EOS;

    ptrfrm = skip_white(ptrfrm);

    ptrto = Op;
    while (delim(*ptrfrm) == NO)
        *ptrto++ = mapdn(*ptrfrm++);
    *ptrto = EOS;

    ptrfrm = skip_white(ptrfrm);

    ptrto = Operand;
    while (*ptrfrm != NEWLINE)
        *ptrto++ = *ptrfrm++;
    *ptrto = EOS;

#ifdef DEBUG
    printf("Label-%s-\n", Label);
    printf("Op----%s-\n", Op);
    printf("Operand-%s-\n", Operand);
#endif
    return (1);
}

/*
 *	process --- determine mnemonic class and act on it
 */
void process()
{
    register struct oper *i;

    Old_pc = Pc;    /* setup `old' program counter */
    Optr = Operand; /* point to beginning of operand field */

    if (*Op == EOS)
    { /* no mnemonic */
        if (*Label != EOS)
            install(Label, Pc);
    }
    else if ((i = mne_look(Op)) == nullptr)
    {
        char msg[80];
        sprintf(msg, "Unrecognized Mnemonic '%s'", Op);
        error(msg);
    }
    else if (i->opClass == PSEUDO)
        do_pseudo(i->opcode);
    else
    {
        if (*Label)
            install(Label, Pc);
        if (Cflag)
            Cycles = i->cycles;
        do_op(i->opcode, i->opClass);
        if (Cflag)
            Ctotal += Cycles;
    }
}
