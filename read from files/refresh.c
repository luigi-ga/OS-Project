#include "read_from_files.h"

#include <signal.h>
#include <unistd.h>
#include <time.h>



#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>




void sig_handler(int signum) {
    write(STDOUT_FILENO, "\e[1;1H\e[2J", 11);
    alarm(1);
}


void print_top() {
    time_t rawtime;
    time(&rawtime);    
    struct tm *time = localtime(&rawtime);
    LoadAvg *loads = (LoadAvg*)malloc(sizeof(LoadAvg));
    get_loadavg(loads);
    double uptime;
    get_uptime(&uptime);
    printf("top - %.2d:%.2d:%.2d up %d min, 0 users, load average: %.2f, %.2f, %.2f\n", 
            time->tm_hour, time->tm_min, time->tm_sec,
            (int) uptime/60, 
            loads->load0, loads->load1, loads->load2);
    

    MemInfo *mem = (MemInfo*)malloc(sizeof(MemInfo));
    get_meminfo(mem);
    printf("MiB Mem: %.1f total, %.1f free, %.1f used, %.1f buff/cache\n", 
            MiB(mem->memTotal), 
            MiB(mem->memFree), 
            MiB((mem->memTotal - mem->memFree)), 
            MiB(mem->buffers));
    printf("MiB Swap: %.1f total, %.1f free, %.1f used, %.1f avail Mem\n", 
            MiB(mem->swapTotal), 
            MiB(mem->swapFree), 
            MiB((mem->swapTotal - mem->swapFree)), 
            MiB(mem->memAvailable));

    ProcInfo *proc = (ProcInfo*)malloc(sizeof(ProcInfo));
    get_procinfo(proc, 1);

    printf("PID: %d\nCOMMAND: %s\nS: %c\nPR: %ld\nNI: %ld\nTIME+: %ld\nVIRT: %lu\nRES: %ld\n",
            proc->pid, 
            proc->command, 
            proc->state, 
            proc->priority, 
            proc->nice, 
            (long int) (uptime - proc->starttime)/60,
            (long int) MiB(proc->virt), 
            proc->res);
    
    
    free(proc);    
    free(loads);
    free(mem);
}



int main() {
    signal(SIGALRM, sig_handler); // Register signal handler
    alarm(1);                     // Scheduled alarm after 2 seconds

    while(1) {
        print_top();
        sleep(1);
    }
    return 0;
}