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

    //CICLO FOR SUI PID
    ProcInfo *proc = (ProcInfo*)malloc(sizeof(ProcInfo));
    get_procinfo(proc, 157);

    printf("PID: %d\nPR: %ld\nNI: %ld\nVIRT: %lu\nRES: %ld\nS: %c\n%%CPU: %.1f\n%%MEM: %.1f\nTIME+: %ld\nCOMMAND: %s\n",
            proc->pid, 
            proc->priority,            
            proc->nice,             
            (long int) MiB(proc->virt), 
            proc->res,
            proc->state, 
            (float) (proc->utime + proc->stime + proc->cutime + proc->cstime) / (uptime - (proc->starttime / 100)),
            25.5,
            (long int) (uptime - proc->starttime),
            proc->command);
    
    //printf("The PID %d has spent %lds in user mode, %lds in kernel mode. Total CPU usage is %lds\n", proc->pid, proc->utime / 100, proc->stime / 100, (proc->utime + proc->stime)/100);
    //printf("The process has been running for %lds. So, the process has used %lf%% of CPU\n", (long int) (uptime - proc->starttime / 100), (proc->utime + proc->stime) / (uptime - (proc->starttime / 100)));
    
    
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