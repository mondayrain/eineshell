#include <cstdio>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "process.h"
#include "shell.h"

Process* Process::background_processes = nullptr;

Process::Process() {}
Process::Process(const char* command_name, char* const* command_args, pid_t pid)
        : next_process(nullptr), command_name(command_name), command_args(command_args), pid(pid) {}

void Process::print_background_processes() {
    /** TODO: We should have callbacks or something to detect if the status of a process has changed.
    * As it is, we can't do stuff like suspend jobs.
    */

    Process* curr = background_processes;
    int retval = 0;
    // Delete the ones that don't actually exist anymore
    while(curr != nullptr) {
        // Check if the process actually exists on the system
        retval = kill(curr->pid, 0);
        if (retval != 0) {
            // Process doesn't exist! delete this node in the linked list
            Process* temp = curr;
            if(curr == background_processes) {
                background_processes = curr->next_process;
            }
            curr = curr->next_process;
            delete temp;
        } else {
            curr = curr->next_process;
        }
    }

    // Print the processes
    curr = background_processes;
    while(curr != nullptr) {
        printf("[%d] %s\n", curr->pid, curr->command_name);
        curr = curr->next_process;
    }

    printf("\n");

}

bool Process::add_to_background_processes(Process* new_process) {
    if (background_processes == nullptr) {
        background_processes = new_process;
        return true;
    }

    Process* curr = background_processes;
    while(curr->next_process != nullptr) {
        curr = curr->next_process;
    }

    curr->next_process = new_process;

    return true;
}

bool Process::remove_from_background_processes(pid_t pid) {
    // TODO: Remove process from running list of processes
    return true;
}

void Process::setup_and_exec_process(bool foreground) {
/**
 * Method called by a child process as soon as it has been forked.
 * It does the pgid & signal handling setup before calling exec on the
 * argument it should call.
// */

    // If the parent launched the child with the intent of
    // making it a background process, then make it a different process group
    // so that Ctrl-C doesn't kill it even if it's supposed to be in the background
    // of the terminal.
    if (!foreground) {
        setpgid (this->pid, this->pid);

        // Prevent the process from writing to stdout
        int devNull = open("/dev/null", O_WRONLY);
        dup2(devNull, STDOUT_FILENO);
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


