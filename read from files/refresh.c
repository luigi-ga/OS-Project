#include "read_from_files.h"

#include <signal.h>
#include <unistd.h>
#include <time.h>


void sig_handler(int signum) {
    write(STDOUT_FILENO, "\e[1;1H\e[2J", 11);
    alarm(1);
}

void print_man() {
    time_t rawtime;
    time(&rawtime);    
    struct tm *time = localtime(&rawtime);
    LoadAvg *loads = (LoadAvg*)malloc(sizeof(LoadAvg));
    get_loadavg(loads);
    double uptime;
    get_uptime(&uptime);
    printf("top - %d:%d:%d up %d min, 0 users, load average: %.2f, %.2f, %.2f\n", 
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
}

int main() {
    signal(SIGALRM, sig_handler); // Register signal handler
    alarm(1);                     // Scheduled alarm after 2 seconds

    while(1) {
        print_man();
        sleep(1); // Delay for 1 second
    }
    return 0;
}