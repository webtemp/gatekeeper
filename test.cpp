#include <cstdio>
#include <unistd.h> // Unix headers UNIx STandarD
#include <thread>
#include <sys/time.h> // For the time struct
#include <sys/resource.h> // For the rusage

/*  typedef struct {
    struct timeval ru_utime; // User time used
    struct timeval ru_stime; // System time used
    long ru_maxrss;        // Maximum resident set size
    long ru_ixrss;         // Integral shared memory size
    long ru_idrss;         // Integral unshared data size
    long ru_isrss;         // Integral unshared stack size
    long ru_minflt;        // Page reclaims
    long ru_majflt;        // Page faults
    long ru_nswap;         // Swaps
    long ru_inblock;       // Block input operations
    long ru_oublock;       // Block output operations
    long ru_msgsnd;        // Messages sent
    long ru_msgrcv;        // Messages received
    long ru_nsignals;      // Signals received
    long ru_nvcsw;         // Voluntary context switches
    long ru_nivcsw;        // Involuntary context switches
} rusage;
*/

#define ONE_MB_IN_KB 1048576

void debugUsage(struct rusage usage) {
    printf("System Time Taken: %ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    printf("User Time Taken: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Maximum resident set size (MB): %.9f\n", ((float)usage.ru_maxrss / 1048576.0)); // 978944 1048576
    printf("Integral shared memory size: %ld\n", usage.ru_ixrss);
    printf("Integral unshared data size: %ld\n", usage.ru_idrss);
    printf("Integral unshared stack size: %ld\n", usage.ru_isrss);
    printf("Page reclaims: %ld\n", usage.ru_minflt);
    printf("Page faults: %ld\n", usage.ru_majflt);
    printf("Swaps: %ld\n", usage.ru_nswap);
    printf("Block input operations: %ld\n", usage.ru_inblock);
    printf("Block output operations: %ld\n", usage.ru_oublock);
    printf("Messages sent: %ld\n", usage.ru_msgsnd);
    printf("Messages received: %ld\n", usage.ru_msgrcv);
    printf("Signals received: %ld\n", usage.ru_nsignals);
    printf("Voluntary context switches: %ld\n", usage.ru_nvcsw);
    printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);
}

int spawn_child() {
    printf("Starting the sub-program.\n");
    pid_t pid = fork();

    if (pid == 0) { // We are now in the Child process
        usleep(988156); // Sleep for 0.988156 seconds or 988156 microseconds
    }
    else if (pid > 0) { // We are now in the PARENT ROCESS
        int status, options = 0;
        struct rusage usage;
        struct timeval time;
        pid_t cpid = wait4(pid, &status, options, &usage);

        // Debug the info from the child program 
        debugUsage(usage);
    }
    else { // Fork Failed
        printf("Forking FAILED!\nPlease contact the systems administrator.");
        return 1;
    }

    printf("\nProgram Terminated Normally\n");

    return 0;
}


int main(int argc, char **argv) {
    std::thread program(spawn_child);

    program.join();

    return 0;
}
