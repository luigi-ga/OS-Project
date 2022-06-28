#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define MiB(mem) (float) mem /(1<<10)

#define handle_error(msg)   do { perror(msg); exit(EXIT_FAILURE); } while (0)


typedef struct LoadAvg {
    float load0;
    float load1;
    float load2;
} LoadAvg;

typedef struct MemInfo {
    unsigned long memTotal;
    unsigned long memFree;
    unsigned long buffers;
    unsigned long swapTotal;
    unsigned long swapFree;
    unsigned long cached;
} MemInfo;


#endif