#include <cstdio>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "process.h"
#include "shell.h"

Process::Process() {}
Process::Process(const char* command_name, char* const* command_args, pid_t pid)
        : next_process(nullptr), command_name(command_name), command_args(command_args), pid(pid) {}

bool Process::add_to_processes(Process* process) {
    // TODO: Add process to running list of processes
    return true;

}
bool Process::remove_from_processes(pid_t pid) {
    // TODO: Remove process from running list of processes
    return true;
}

void Process::setup_and_exec_process(bool foreground) {
/**
 * Method called by a child process as soon as it has been forked.
 * It does the pgid & signal handling setup before calling exec on the
 * argument it should call.
 */
    // If the parent launched the child with the intent of
    // making it the foreground process, then let it take control
    // of the terminal.
    if (foreground) {
        tcsetpgrp(terminal_fd, this->pid);
    }

    // The child inherits signal handling from the spawning process.
    // Since the spawning process is a shell (which ignores stuff like SIGINT in order
    // to pass on the signal) we need to restore our default signal handling.
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);

    // Execute the process!
    int retval = execvp(this->command_name, this->command_args);

    // Handle errors
    if(retval == -1) {
        if (errno == 2) {
            printf("ERROR: Could not find program '%s'\n", command_name);
            //} else if (errno == EACCES) {
            //    // TODO: This is what is returned on an incorrect command on ugrad Linux
            //    printf("ERROR: You do not have permission to run '%s'\n", command_name);
        } else {
            printf("ERROR: Could not run program '%s'; error number returned: %d\n", command_name, errno);
        }
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


