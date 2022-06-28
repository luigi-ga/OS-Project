#include "read_from_files.h"

void get_loadavg(LoadAvg *loads) {      
    ssize_t read, len = 0;
    char *line;
    // check if loads have been initialized
    if(loads == NULL) handle_error("ERROR (get_loadavg): loads not initialized");
    // open loadavg file; check for errors in fopen
    FILE *fp = fopen("/proc/loadavg", "r");
    if(fp == NULL) handle_error("ERROR (get_loadavg): fopen /proc/loadavg file");
    // get values of loadavg and side effect on loads
    while((read = getline(&line, (long unsigned int*) &len, fp)) != -1) {
        if(sscanf(line, "%f %f %f", &loads->load0, &loads->load1, &loads->load2)) break;
    }
    // close loadavg file
    if(fclose(fp)) handle_error("ERROR (get_loadavg): fclose /proc/loadavg file");
}

void get_meminfo(MemInfo *mem) {
    ssize_t read, len = 0;
    char *line;
    // check if mem have been initialized
    if(mem == NULL) handle_error("ERROR (get_meminfo): mem not initialized");
    // open meminfo file; check for errors in fopen
    FILE *fp = fopen("/proc/meminfo", "r");
    if(fp == NULL) handle_error("ERROR (get_meminfo): fopen /proc/meminfo file");    
    // get values and side effect on mem
    while((read = getline(&line, (long unsigned int*) &len, fp)) != -1) {
        sscanf(line, "MemTotal: %ld kB", &mem->memTotal);
        sscanf(line, "MemTotal: %ld kB", &mem->memTotal);
        sscanf(line, "MemFree: %ld kB", &mem->memFree);
        sscanf(line, "MemAvailable: %ld kB", &mem->memAvailable);
        sscanf(line, "SwapTotal: %ld kB", &mem->swapTotal);
        sscanf(line, "SwapFree: %ld kB", &mem->swapFree);
    }
    // close meminfo file */
    if(fclose(fp)) handle_error("ERROR (get_meminfo): fclose /proc/loadavg file");
}

void get_uptime(double *uptime) {
    ssize_t read, len = 0;
    char *line;
    // open uptime file; check for errors in fopen
    FILE *fp = fopen("/proc/uptime", "r");
    if(fp == NULL) handle_error("ERROR (get_uptime): fopen /proc/uptime file");
    // get values of loadavg and side effect on loads
    while((read = getline(&line, (long unsigned int*) &len, fp)) != -1) {
        if(sscanf(line, "%lf", uptime)) break;
    }
    // close loadavg file
    if(fclose(fp)) handle_error("ERROR (get_uptime): fclose /proc/uptime file");

}

