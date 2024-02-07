/* Startup for apout. Parse arguments, load the binary, and run it.
 */

#include <assert.h>
#include "defines.h"

/* The following array holds the FILE pointers that correspond to open file
 * descriptors. Only fds which are not ttys have FILE * pointers
 */
FILE *stream[NFILE];
char *streammode[NFILE]; /* Mode for each file - used for dup */

/* The following two buffers are used as */
/* part of the translation from virtal */
/* absolute filenames to native ones. We */
/* only have 2 buffers, so if you call */
/* xlate_filename() 3 times, the 1st return */
/* value will be destroyed. */
static char realfilename[2][2 * MAXPATHLEN];
static char *rfn[2];
static int whichrfn = 0;
char *apout_root = NULL; /* Root dir for simulated a.out */

void usage()
{
    fprintf(stderr, "Usage: apout");
    fprintf(stderr, " pdp11_binary\n");
    exit(1);
}

int main(int argc, char **argv)
{
    int i;

    /* Ensure, before we start, that certain types are right */
    assert(sizeof(int8_t) == 1);
    assert(sizeof(u_int8_t) == 1);
    assert(sizeof(int16_t) == 2);
    assert(sizeof(u_int16_t) == 2);
    assert(sizeof(int32_t) == 4);
    assert(sizeof(u_int32_t) == 4);

    if (argc < 2)
        usage();
    if (!strcmp(argv[1], "-help"))
        usage();
    if (!strcmp(argv[1], "--help"))
        usage();

    /* Prepare arg list for emulated environment */
    argc--;
    argv++;
    Argc = argc;
    Envp[0] = NULL;
    for (i = 0; i < argc; i++)
        Argv[i] = argv[i];

    /* Initialise the stream pointers */
    for (i = 3; i < NFILE; i++) {
        stream[i] = NULL;
        streammode[i] = NULL;
    }
    stream[0] = stdin;
    streammode[0] = "r";
    stream[1] = stdout;
    streammode[1] = "w";
    stream[2] = stderr;
    streammode[2] = "w";

    /* Set the translation to a fictitious */
    /* root filesystem */
    if ((apout_root = getenv("APOUT_ROOT"))) {
        set_apout_root(apout_root);
    } else {
#ifdef APOUT_DONT_ASSUME_ROOT
        fprintf(stderr,
                "APOUT_ROOT env variable not set before running apout\n");
        exit(1);
#else
        set_apout_root("/");
#endif
    }

    /* Try to load the binary as an a.out */
    if (load_a_out(argv[0], NULL, 1) == -1) {
        fprintf(stderr, "Apout - couldn't load %s\n", argv[0]);
        exit(1);
    }

    /* Other emulated systems (RT-11) can go here */

    run(); /* Now run the binary */
    exit(0);
}

/* Translate from a filename to one which is possibly rooted in $APOUT_ROOT.
 * Note we return a pointer to one of two buffers. The caller does not
 * have to free the returned pointer, but successive calls will destroy
 * calls from >2 calls earlier.
 */
char *xlate_filename(char *name)
{
    int i = whichrfn;

    if (name == NULL)
        return (NULL);
    if (name[0] == '\0')
        return ("."); /* Undocumented, but used in V7 */
    if (name[0] != '/')
        return (name);       /* Relative, keep it relative */
    strcpy(rfn[i], name);    /* Copy name into buffer */
    whichrfn = 1 - whichrfn; /* Switch to other buffer next time */
    return (realfilename[i]);
}

void set_apout_root(char *dirname)
{
    strcpy(realfilename[0], dirname);
    strcpy(realfilename[1], dirname);
    rfn[0] = realfilename[0];
    rfn[0] += strlen(realfilename[0]);
    rfn[1] = realfilename[1];
    rfn[1] += strlen(realfilename[1]);
}
