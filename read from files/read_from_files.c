#include "read_from_files.h"

void get_loadavg(LoadAvg *loads) {  
    // check if loads have been initialized
    if(loads == NULL) handle_error("ERROR (get_loadavg): loads not initialized");
    // open loadavg file; check for errors in fopen
    FILE *fp = fopen("/proc/loadavg", "r");
    if(fp == NULL) handle_error("ERROR (get_loadavg): fopen /proc/loadavg file");
    // get values of loadavg and side effect on loads; errors if less than 3 values are read
    if(fscanf(fp, "%f %f %f", &loads->load0, &loads->load1, &loads->load2) != 3) handle_error("ERROR (get_loadavg): fscanf /proc/loadavg file");
    // close loadavg file
    if(fclose(fp)) handle_error("ERROR (get_loadavg): fclose /proc/loadavg file");
}

void get_meminfo(MemInfo *mem) {
    // check if mem have been initialized
    if(mem == NULL) handle_error("ERROR (get_meminfo): mem not initialized");
    // open meminfo file; check for errors in fopen
    FILE *fp = fopen("/proc/meminfo", "r");
    if(fp == NULL) handle_error("ERROR (get_meminfo): fopen /proc/meminfo file");
    // get values and side effect on mem; check for errors
    if(!fscanf(fp, "MemTotal: %ld kB", &mem->memTotal)) handle_error("ERROR (get_meminfo): fscanf [MemTotal] /proc/meminfo file");
    if(!fscanf(fp, "\nMemFree: %ld kB", &mem->memFree)) handle_error("ERROR (get_meminfo): fscanf [MemFree] /proc/meminfo file");
    if(!fscanf(fp, "\nBuffers: %ld kB", &mem->buffers)) handle_error("ERROR (get_meminfo): fscanf [Buffers] /proc/meminfo file");
    //if(fscanf(fp, "\nSwapTotal: %ld kB", &mem->swapTotal)) handle_error("ERROR (get_meminfo): fscanf [SwapTotal] /proc/meminfo file");
    //if(!fscanf(fp, "SwapFree: %ld kB", &mem->swapFree)) handle_error("ERROR (get_meminfo): fscanf [SwapFree] /proc/meminfo file");
    if(fscanf(fp, "Cached: %ld kB", &mem->cached)) handle_error("ERROR (get_meminfo): fscanf [Cached] /proc/meminfo file");
    // close meminfo file
    if(fclose(fp)) handle_error("ERROR (get_meminfo): fclose /proc/loadavg file");
}

int main() {
    LoadAvg *loads = (LoadAvg*)malloc(sizeof(LoadAvg));
    get_loadavg(loads);
    printf("%.2f, %.2f, %.2f\n", loads->load0, loads->load1, loads->load2);

    MemInfo *mem = (MemInfo*)malloc(sizeof(MemInfo));
    get_meminfo(mem);
    printf("MiB Mem: %.1f total, %.1f free, %.1f used, %.1f buff/cache", MiB(mem->memTotal), MiB(mem->memFree), 54.8, 3.2);
}