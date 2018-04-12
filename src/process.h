#ifndef EINESHELL_PROCESS_CONTROL_H
#define EINESHELL_PROCESS_CONTROL_H

#include <sys/types.h>
#include <termios.h>

/* A process is a single process.  */
class Process {
public:
    // Running list of all processes
    static Process *background_processes;

    Process();
    Process(const char* command_name, char* const* command_args, pid_t pid);

    static bool add_to_background_processes(Process* process);
    static bool remove_from_background_processes(pid_t pid);

    void setup_and_exec_process(bool foregound);

private:
    Process* next_process;     /* The next process in the chain */
    const char* command_name;  /* first arg to execvp */
    char* const* command_args;  /* second arg to execvp */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
};


#endif //EINESHELL_PROCESS_CONTROL_H
