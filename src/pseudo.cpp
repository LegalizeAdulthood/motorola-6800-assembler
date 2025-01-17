/*
 *      pseudo --- pseudo op processing
 */

#include "as.h"
#include "eval.h"
#include "globals.h"
#include "symtab.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iterator>
#include <string>

#define RMB     0  /* Reserve Memory Bytes         */
#define FCB     1  /* Form Constant Bytes          */
#define FDB     2  /* Form Double Bytes (words)    */
#define FCC     3  /* Form Constant Characters     */
#define ORG     4  /* Origin                       */
#define EQU     5  /* Equate                       */
#define ZMB     6  /* Zero memory bytes            */
#define FILL    7  /* block fill constant bytes    */
#define OPT     8  /* assembler option             */
#define NULL_OP 9  /* null pseudo op               */
#define PAGE    10 /* new page                     */
#define CPU     11 /* specify cpu variant          */

struct oper pseudo[] = {
    {"bsz", PSEUDO, ZMB, 0},     {"cpu", PSEUDO, CPU, 0},
    {"end", PSEUDO, NULL_OP, 0}, {"equ", PSEUDO, EQU, 0},
    {"fcb", PSEUDO, FCB, 0},     {"fcc", PSEUDO, FCC, 0},
    {"fdb", PSEUDO, FDB, 0},     {"fill", PSEUDO, FILL, 0},
    {"nam", PSEUDO, NULL_OP, 0}, {"name", PSEUDO, NULL_OP, 0},
    {"opt", PSEUDO, OPT, 0},     {"org", PSEUDO, ORG, 0},
    {"pag", PSEUDO, PAGE, 0},    {"page", PSEUDO, PAGE, 0},
    {"rmb", PSEUDO, RMB, 0},     {"spc", PSEUDO, NULL_OP, 0},
    {"ttl", PSEUDO, NULL_OP, 0}, {"zmb", PSEUDO, ZMB, 0}};

CpuType cpuType = CPU_UNKNOWN;

int sizeof_pseudo() { return sizeof(pseudo); }

static std::string to_lower(const char *text)
{
    std::string result;
    std::transform(text, text + std::strlen(text), std::back_inserter(result),
                   [](char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

/*
 *      do_pseudo --- do pseudo op processing
 */
void do_pseudo(int op /* which op */)
{
    char fccdelim;
    int j;
    int fill;

    if (op != EQU && *Label)
        install(Label, Pc);

    P_force++;
    switch (op)
    {
    case RMB: /* reserve memory bytes */
        if (eval())
        {
            Pc += Result;
            f_record(); /* flush out bytes */
        }
        else
            error("Undefined Operand during Pass One");
        break;
    case ZMB: /* zero memory bytes */
        if (eval())
            while (Result--)
                emit(0);
        else
            error("Undefined Operand during Pass One");
        break;
    case FILL: /* fill memory with constant */
        eval();
        fill = Result;
        if (*Optr++ != ',')
            error("Bad fill");
        else
        {
            Optr = skip_white(Optr);
            eval();
            while (Result--)
                emit(fill);
        }
        break;
    case FCB: /* form constant byte(s) */
        do
        {
            Optr = skip_white(Optr);
            eval();
            if (Result > 0xFF)
            {
                if (!Force_byte)
                    warn("Value truncated");
                Result = lobyte(Result);
            }
            emit(Result);
        } while (*Optr++ == ',');
        break;
    case FDB: /* form double byte(s) */
        do
        {
            Optr = skip_white(Optr);
            eval();
            eword(Result);
        } while (*Optr++ == ',');
        break;
    case FCC: /* form constant characters */
        if (*Operand == EOS)
            break;
        fccdelim = *Optr++;
        while (*Optr != EOS && *Optr != fccdelim)
            emit(*Optr++);
        if (*Optr == fccdelim)
            Optr++;
        else
            error("Missing Delimiter");
        break;
    case ORG: /* origin */
        if (eval())
        {
            Old_pc = Pc = Result;
            f_record(); /* flush out any bytes */
        }
        else
            error("Undefined Operand during Pass One");
        break;
    case EQU: /* equate */
        if (*Label == EOS)
        {
            error("EQU requires label");
            break;
        }
        if (eval())
        {
            install(Label, Result);
            Old_pc = Result; /* override normal */
        }
        else
            error("Undefined Operand during Pass One");
        break;
    case OPT: /* assembler option */
        P_force = 0;
        if (head(Operand, "l"))
            Lflag = 1;
        else if (head(Operand, "nol"))
            Lflag = 0;
        else if (head(Operand, "c"))
        {
            Cflag = 1;
            Ctotal = 0;
        }
        else if (head(Operand, "noc"))
            Cflag = 0;
        else if (head(Operand, "contc"))
        {
            Cflag = 1;
        }
        else if (head(Operand, "s"))
            Sflag = 1;
        else if (head(Operand, "cre"))
            CREflag = 1;
        else if (head(to_lower(Operand).c_str(), "cmos"))
            cpuType = CPU_M6805;
        else
            error((std::string{"Unrecognized OPT '"} + Operand + "'").c_str());
        break;
    case PAGE: /* go to a new page */
        P_force = 0;
        N_page = 1;
        if (Pass == 2)
            if (Lflag)
            {
                printf("\f");
                printf("%-10s", Argv[Cfn]);
                printf("                                   ");
                printf("page %3d\n", Page_num++);
            }
        break;
    case NULL_OP: /* ignored psuedo ops */
        P_force = 0;
        break;
    case CPU:
        if (head(Operand, "cmos"))
            cpuType = CPU_M6805;
        else if (head(Operand, "hc05c4"))
            cpuType = CPU_HC05C4;
        else
        {
            char msg[80];
            sprintf(msg, "Unrecognized CPU type '%s'", Operand);
            error(msg);
        }
        break;
    default:
        fatal("Pseudo error");
    }
}
