/* cpu.c - this holds the main loop for the emulator, plus generic
 * functions to deal with exceptional instructions and events
 */
#include <unistd.h>
#include "defines.h"

uint8_t *ispace, *dspace; /* Instruction and Data spaces */
uint16_t dwrite_base = 2; /* Lowest addr where dspace writes can occur */

uint16_t regs[8]; /* general registers */
uint16_t ir;      /* current instruction register */
uint16_t *adptr;  /* used in memory access macros */
uint16_t ea_addr; /* stored address for dest modifying insts */

int CC_N = 0; /* The processor status word is represented */
int CC_Z = 0; /* by these four values. On some */
int CC_V = 0; /* architectures, you may get a performance */
int CC_C = 0; /* increase by using shorts or bytes */

uint16_t dstword; /* These globals are used in the effective */
uint16_t srcword; /* address calculations, mainly to save */
uint16_t tmpword; /* parameter passing overheads in */
uint8_t dstbyte;  /* function calls */
uint8_t srcbyte;
uint8_t tmpbyte;
struct our_siglist *Sighead = NULL; /* List of pending signals */
struct our_siglist *Sigtail = NULL; /* List of pending signals */
void (*sigrunner)(void) = NULL;     /* F'n that will run the signal */

/* Run until told to stop. */
void run()
{
    while (1) {
        /* Fetch and execute the instruction. */
        /* manually unroll this inner loop */
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        lli_word(regs[PC], ir);
        regs[PC] += 2;
        itab[ir >> 6]();
        if ((Sighead != NULL) && (sigrunner != NULL))
            (void) (*sigrunner)();
    }
}

/* sim_init() - Initialize the cpu registers. */
void sim_init()
{
    int x;

    for (x = 0; x < 8; ++x) {
        regs[x] = 0;
    }
    ir = 0;
    CLR_CC_ALL();
}

void bus_error(int signo)
{
    exit(EXIT_FAILURE);
}

void seg_fault()
{
    exit(EXIT_FAILURE);
}

void waiti()
{
    exit(EXIT_FAILURE);
}

void halt()
{
    exit(EXIT_FAILURE);
}

void iot()
{
    exit(EXIT_FAILURE);
}

void emt()
{
    exit(EXIT_FAILURE);
}

void bpt()
{
    exit(EXIT_FAILURE);
}

void illegal()
{
    exit(EXIT_FAILURE);
}

void not_impl()
{
    exit(EXIT_FAILURE);
}

void mark()
{
    exit(EXIT_FAILURE);
}

void mfpd()
{
    exit(EXIT_FAILURE);
}

void mtpd()
{
    exit(EXIT_FAILURE);
}

void trap()
{
    exit(EXIT_FAILURE);
}

void bad_FP_reg()
{
    exit(EXIT_FAILURE);
}

/* This is the generic function which catches
 * a signal, and appends it to the queue.
 */
void sigcatcher(int sig)
{
    struct our_siglist *this;

    this = (struct our_siglist *) malloc(sizeof(struct our_siglist));
    if (this == NULL)
        return;

    this->sig = sig;
    this->next = NULL;
    if (Sighead == NULL) {
        Sighead = Sigtail = this;
    } else {
        Sigtail->next = this;
        Sigtail = this;
    }
}
