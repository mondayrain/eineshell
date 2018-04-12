#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>
#include <algorithm>
#include "shell.h"
#include "environment.h"
#include "execute.h"
#include "builtin.h"
#include "process.h"
#include "helpers.h"

using std::string;
using std::transform;
using std::back_inserter;

std::map<pid_t, std::string> PID_MAP = {};

int execute_command(std::vector<std::string> tokens) {
/* Returns 1 if the command is exit,
 * and -1 if there was an error.
 * Returns 0 otherwise.
 * */

    // TODO: Official error codes? https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html#Error-Codes
    // https://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#Error-Messages
    std::string command_name = tokens[0];
    if(is_built_in(command_name)) {
        return call_built_in(command_name);
    } else if (is_built_in_with_args(command_name)) {
        return call_built_in_with_args(command_name, tokens.begin()+1, tokens.end());
    } else {
        return call(tokens);
    }
}

bool is_built_in(std::string command_name) {
    for(int i=0; i < BUILTINS.size(); i++) {
        if(command_name.compare(BUILTINS[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_built_in_with_args(std::string command_name) {
    for(int i=0; i < BUILTINS_WITH_ARGS.size(); i++) {
        if(command_name.compare(BUILTINS_WITH_ARGS[i]) == 0) {
            return true;
        }
    }
    return false;
}

int call_built_in(std::string command_name) {
    for (int i=0; i < BUILTINS.size(); i++) {
        if (command_name.compare(BUILTINS[i]) == 0) {
            return BUILTIN_FUNCTIONS[i]();
        }
    }

    // Theoretically this should never happen
    return -1;
}

int call_built_in_with_args(std::string command_name, std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) {
    for (int i=0; i < BUILTINS_WITH_ARGS.size(); i++) {
        if (command_name.compare(BUILTINS_WITH_ARGS[i]) == 0) {
            return BUILTIN_FUNCTIONS_WITH_ARGS[i](args_begin, args_end);
        }
    }

    // Theoretically this should never happen
    return -1;
}


int call(std::vector<std::string> tokens) {
    /**
     * This method calls a non-builtin program that we expect to
     * be found in the PATH. In order to support process control,
     * we make sure to set the proper process group IDs after fork/exec.
     */
    bool foreground_command = true;
    char *command_name = (char *) tokens[0].c_str();
    char *empty_argv[] = { command_name, NULL };
    std::vector<char*> args_array;

    if (tokens.size() > 1) {
        if (tokens[tokens.size()-1] == "&") {
            std::transform(tokens.begin(), tokens.end()-1, std::back_inserter(args_array), convert);
        } else { 
            std::transform(tokens.begin(), tokens.end(), std::back_inserter(args_array), convert);
        }
    }

    // If we're running a background job, don't bother waiting
    if(tokens[tokens.size()-1] == "&") {
        foreground_command = false;
    }

    // Fork and execute!
    pid_t pid = fork();
    if (pid == -1) {
        // Forking the child failed...
        printf("ERROR: Couldn't spawn child process to run your command.");
    }

    // At this point, both child and parent are exactly the same.
    // Fork returns 0 to the child and the pid of the child to the parent.
    if(pid == 0){
        // CHILD
        // Create the Process object to be used
        pid_t pid = getpid();
        Process p = Process();
        if (tokens.size() > 1) {
            p = Process(command_name, &args_array[0], pid);
        } else {
            p = Process(command_name, empty_argv, pid);
        }

        // Launch the process
        p.setup_and_exec_process(foreground_command);
    } else {
        // PARENT
        int status = 0;

        if(foreground_command) {
            pid_t child_pid = waitpid(pid, &status, 0);
        } else {
            // We need to keep track of background processes
            Process *p = nullptr;
            if (tokens.size() > 1) {
                p = new Process(command_name, &args_array[0], pid);
            } else {
                p = new Process(command_name, empty_argv, pid);
            }

            Process::add_to_background_processes(p);
            printf("\n[%d] Running %s in the background\n", pid, command_name);
        }
        if(status != 0) {
            if(WIFSIGNALED(status)) {
                printf("Program '%s terminated by a signal'\n\n", command_name);
            }
            // No need for an else since the child process will write the error message
            // if it errored out
        }

        printf("\n");
    }

    return 0;
}
