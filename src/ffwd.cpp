/*
 *      file I/O version of forward ref handler
 */

#include "config.h"

#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_IO_H
#include <io.h>
#include <sys/stat.h>
#endif
#include <fcntl.h>

#include "ffwd.h"
#include "globals.h"
#include "util.h"

#if HAVE_UNISTD_H
#define FILEMODE 0644 /* file creat mode */
#else
#if HAVE_IO_H
#define FILEMODE (S_IREAD | S_IWRITE)
#endif
#endif
#define UPDATE 2 /* file open mode */
#define ABS    0 /* absolute seek */

int Forward = 0; /* temp file's file descriptor	*/
char Fwd_name[] = {"Fwd_refs"};

/*
 *      fwdinit --- initialize forward ref file
 */
void fwdinit(void)
{
    Forward = creat(Fwd_name, FILEMODE);
    if (Forward < 0)
        fatal("Can't create temp file");
    close(Forward); // close and reopen for reads and writes
    Forward = open(Fwd_name, UPDATE);
    if (Forward < 0)
        fatal("Forward ref file has gone.");
#ifndef DEBUG
    unlink(Fwd_name);
#endif
}

/*
 *      fwdreinit --- reinitialize forward ref file
 */
void fwdreinit(void)
{
    F_ref = 0;
    Ffn = 0;
    lseek(Forward, 0L, ABS); // rewind forward refs
    read(Forward, &Ffn, sizeof(Ffn));
    read(Forward, &F_ref, sizeof(F_ref)); // read first forward ref into mem
#ifdef DEBUG
    printf("First fwd ref: %d,%d\n", Ffn, F_ref);
#endif
}

/*
 *      fwdmark --- mark current file/line as containing a forward ref
 */
void fwdmark(void)
{
    write(Forward, &Cfn, sizeof(Cfn));
    write(Forward, &Line_num, sizeof(Line_num));
}

/*
 *      fwdnext --- get next forward ref
 */
void fwdnext(void)
{
    int stat;

    stat = read(Forward, &Ffn, sizeof(Ffn));
#ifdef DEBUG
    printf("Ffn stat=%d ", stat);
#endif
    stat = read(Forward, &F_ref, sizeof(F_ref));
#ifdef DEBUG
    printf("F_ref stat=%d  ", stat);
#endif
    if (stat < 2)
    {
        F_ref = 0;
        Ffn = 0;
    }
#ifdef DEBUG
    printf("Next Fwd ref: %d,%d\n", Ffn, F_ref);
#endif
}