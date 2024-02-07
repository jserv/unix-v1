/*
 * Quick hack to read old unix a.out files and make a simh "load file".
 *
 * Copyright (C0 2008 Brad Parker <brad@heeltoe.com>
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/* Binary loader.
 *
 * Loader format consists of blocks, optionally preceded, separated, and
 * followed by zeroes.  Each block consists of:
 *
 *       001             ---
 *       xxx              |
 *       lo_count         |
 *       hi_count         |
 *       lo_origin        > count bytes
 *       hi_origin        |
 *       data byte        |
 *       :                |
 *       data byte       ---
 *       checksum
 *
 *  If the byte count is exactly six, the block is the last on the tape, and
 *  there is no checksum.  If the origin is not 000001, then the origin is
 *  the PC at which to start the program.
 */
struct exec {
    uint16_t a_magic;
    uint16_t a_text;
    uint16_t a_data;
    uint16_t a_bss;
    uint16_t a_syms;
    uint16_t a_entry;
    uint16_t a_unused;
    uint16_t a_flag;
};

unsigned char buffer[1024];
int checksum;

int mk_hdr(int fd, int count, int origin)
{
    checksum = 0;
    int hc = count + 6;

    buffer[0] = 0x01;
    buffer[1] = 0x00;
    buffer[2] = hc & 0xff;
    buffer[3] = hc >> 8;
    buffer[4] = origin & 0xff;
    buffer[5] = origin >> 8;

    int ret = write(fd, buffer, 6);
    if (ret != 6)
        return -1;

    for (int i = 0; i < 6; i++)
        checksum += buffer[i] & 0xff;

    return 0;
}

int mk_post_data(int fd)
{
    /* final checksum must be zero */
    int final_checksum = 256 - (checksum & 0xff);

    buffer[0] = final_checksum;

    int ret = write(fd, buffer, 1);
    if (ret != 1)
        return -1;

    return 0;
}

int load(int fd, char *buf, int bufsize)
{
    printf("load: %d bytes\n", bufsize);

    if (bufsize < 65536) {
        mk_hdr(fd, bufsize, 0);

        int ret = write(fd, buf, bufsize);
        if (ret != bufsize)
            return -1;

        for (int i = 0; i < bufsize; i++)
            checksum += buf[i] & 0xff;

        mk_post_data(fd);
    }

    return 0;
}

void finish(int fd, int origin)
{
    mk_hdr(fd, 0, origin);
}

int process_aout(int ifd, int ofd, int origin)
{
    struct exec hdr;
    char *textblob, *datablob;

    int ret = read(ifd, (char *) &hdr, sizeof(hdr));
    if (ret != sizeof(hdr))
        return -1;

    if (1) {
        printf("magic 0%o\ntext %d, data %d, bss %d, syms %d\n",
               hdr.a_magic & 0xffff, hdr.a_text, hdr.a_data, hdr.a_bss,
               hdr.a_syms);
        printf("entry %o, flag %o\n", hdr.a_entry, hdr.a_flag);
    }

    textblob = malloc(hdr.a_text);
    datablob = malloc(hdr.a_data);

    int hdr_size = 0;

    /* v7 header? if so, 0 is after header */
    switch (hdr.a_magic) {
    case 0407:
        hdr_size = 0;
        break;
    case 0405:
        hdr_size = 12;
        break;
    }

    if (hdr_size) {
        /* back up */
        lseek(ifd, (off_t) -hdr_size, SEEK_CUR);
        hdr.a_text += hdr_size;
    }

    ret = read(ifd, textblob, hdr.a_text);
    if (ret != hdr.a_text)
        return -1;

    ret = read(ifd, datablob, hdr.a_data);
    if (ret != hdr.a_data)
        return -1;

    load(ofd, textblob, hdr.a_text);
    load(ofd, datablob, hdr.a_data);

    finish(ofd, origin);

    return 0;
}

int process(char *inf, char *outf)
{
    int ofd = open(outf, O_WRONLY | O_CREAT, 0666);
    if (ofd < 0) {
        perror(outf);
        return -1;
    }

    int ifd = open(inf, O_RDONLY);
    if (ifd < 0) {
        perror(inf);
        close(ofd);
        return -1;
    }

    int ret = 0;
    int origin = 0;

    if (process_aout(ifd, ofd, origin)) {
        ret = -1;
    }

    close(ifd);
    close(ofd);

    return ret;
}

int main(int argc, char *argv[])
{
    char *filename = "a.out";
    char *output_filename = "loadfile";

    if (argc > 1)
        filename = argv[1];
    if (argc > 2)
        output_filename = argv[2];
    if (process(filename, output_filename)) {
        fprintf(stderr, "%s: failed?\n", filename);
    }

    exit(0);
}
