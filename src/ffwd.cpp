/*
 *      file I/O version of forward ref handler
 */

#include "config.h"

#include <string>

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
void fwdinit()
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
void fwdreinit()
{
    F_ref = 0;
    Ffn = 0;
    lseek(Forward, 0L, ABS); // rewind forward refs
    size_t count = read(Forward, &Ffn, sizeof(Ffn));
    if (count != sizeof(Ffn))
    {
        const std::string msg = "Couldn't read " + std::to_string(sizeof(Ffn)) + " bytes";
        fatal(msg.c_str());
    }
    count = read(Forward, &F_ref, sizeof(F_ref)); // read first forward ref into mem
    if (count != sizeof(F_ref))
    {
        const std::string msg = "Couldn't read " + std::to_string(sizeof(F_ref)) + " bytes";
        fatal(msg.c_str());
    }
#ifdef DEBUG
    printf("First fwd ref: %d,%d\n", Ffn, F_ref);
#endif
}

/*
 *      fwdmark --- mark current file/line as containing a forward ref
 */
void fwdmark()
{
    size_t count = write(Forward, &Cfn, sizeof(Cfn));
    if (count != sizeof(Cfn))
    {
        const std::string msg = "Couldn't write " + std::to_string(sizeof(Cfn)) + " bytes";
        fatal(msg.c_str());
    }
    count = write(Forward, &Line_num, sizeof(Line_num));
    if (count != sizeof(Line_num))
    {
        const std::string msg = "Couldn't write " + std::to_string(sizeof(Line_num)) + " bytes";
        fatal(msg.c_str());
    }
}

/*
 *      fwdnext --- get next forward ref
 */
void fwdnext()
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
