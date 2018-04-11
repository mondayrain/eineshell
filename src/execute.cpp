#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>
#include <algorithm>
#include "environment.h"
#include "execute.h"
#include "builtin.h"
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

    // Fork and execute!
    pid_t pid = fork();

    // At this point, both child and parent are exactly the same.
    // Fork returns 0 to the child and the pid of the child to the parent.
    if(pid == 0){
        // CHILD
        int retval;
        if (tokens.size() > 1) {
            retval = execvp(command_name,  &args_array[0]);
        } else {
            retval = execvp(command_name, empty_argv);
        }

        if(retval == -1) {
            // TODO: Why aren't these returning what I expect?
            if (errno == 2) {
                printf("ERROR: Could not find program '%s'\n", command_name);
            } else if (errno == EACCES) {
                printf("ERROR: You do not have permission to run '%s'\n", command_name);
            } else {
                printf("ERROR: Could not run program '%s'; error number returned: %d\n", command_name, errno);
            }
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        // PARENT
        int status;


        // If we're running a background job, don't bother waiting
        if(tokens[tokens.size()-1] == "&") {
            // TODO: Remove this when proper job control is implemented
            return 0;
        }

        pid_t child_pid = waitpid(pid, &status, 0);
        if(status != NULL) {
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
