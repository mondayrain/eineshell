#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "environment.h"
#include "execute.h"
#include "builtin.h"

std::map<pid_t, std::string> PID_MAP = {};

int execute_command(char* command_name) {
/* Returns 1 if the command is exit,
 * and -1 if there was an error.
 * Returns 0 otherwise.
 * */
    if(is_built_in(command_name)) {
        return call_built_in(command_name);
    } else if (is_built_in_with_args(command_name)) {
        // TODO: Pass arguments
        return call_built_in_with_args(command_name, NULL);
    } else {
        // If the command is not built in, we have to 1) look in our path to find out if
        // the program exists, and 2) spawn program into child process.
        return call(command_name);
    }

    // TODO: Official error codes? https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html#Error-Codes
    // https://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#Error-Messages
}

bool is_built_in(char* command_name) {
    for(int i=0; i < NUM_BUILTINS; i++) {
        if(strcmp(command_name, BUILTINS[i]) == 0) {
            return true;
        }
    }
    return false;
}

int call_built_in(char* command_name) {
    for (int i = 0; i < NUM_BUILTINS; i++) {
        if (strcmp(command_name, BUILTINS[i]) == 0) {
            return BUILTIN_FUNCTIONS[i]();
        }
    }

    // Theoretically this should never happen
    return -1;
}

bool is_built_in_with_args(char* command_name) {
    for(int i=0; i < NUM_BUILTINS_WITH_ARGS; i++) {
        if(strcmp(command_name, BUILTINS_WITH_ARGS[i]) == 0) {
            return true;
        }
    }
    return false;
}

int call_built_in_with_args(char* command_name, char* arg) {
    for (int i = 0; i < NUM_BUILTINS_WITH_ARGS; i++) {
        if (strcmp(command_name, BUILTINS_WITH_ARGS[i]) == 0) {
            return BUILTIN_FUNCTIONS_WITH_ARGS[i](arg);
        }
    }

    // Theoretically this should never happen
    return -1;
}


int call(char* command_name) {
    // TODO: Actually properly look in env var PATH
    char file_path[50];;
    sprintf(file_path, "%s/%s!", "/bin", command_name);

    // Build argv
    // We need to pass as a second argument to argv the name of
    // the calling program; this is the only way for us to know if bash/another shell called eineshell
    // or if eineshell did. This is important because we need to know whether or not to reset environment vars.
    // const char* argv[2] = { "name of program", ENV_VARS_MAP[std::string("EINESHELL_PATH")].c_str() };
    char *argv[] = { file_path, NULL };

    // Fork and execute!
    pid_t pid = fork();
    // At this point, both child and parent are exactly the same.
    // Fork returns 0 to the child and the pid of the child to the parent.
    if(pid == 0){
        // TODO: Properly pass arg Vs when we start to parse args for reals
        int retval = execvp(command_name, argv);
        if(retval == -1) {
            if (errno == 2) {
                printf("ERROR: Could not find program '%s'\n", command_name);
            //} else if (errno == EACCES) {
            //    printf("ERROR: You do not have permission to run '%s'\n", command_name);
            } else {
                //printf("ERROR: Could not run program '%s'; error number returned: %d\n", command_name, errno);
                printf("ERROR: Could not find program '%s'\n", command_name);
            }
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        // TODO: SEE Process Completion Statuses
        // https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html#Process-Completion-Status
        int status;
        pid_t child_pid = waitpid(pid, &status, 0);
        if(status == -1) {
            printf("ERROR: Could not run program '%s'\n\n", command_name);
            return -1;
        }

        printf("\n");
    }

    return 0;
}
