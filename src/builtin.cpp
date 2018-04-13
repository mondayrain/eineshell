#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <signal.h>
#include <string>
#include <vector>
#include <iostream>
#include "environment.h"
#include "process.h"

using std::string;
using std::vector;
using std::distance;
using std::cout;

/*-----------------*/
/* -- HELPERS -- */
/*-----------------*/
char* _getenvvar(const char* env_var_name) {
    char* result;
    result = getenv(env_var_name);
    return result;
}

/*-----------------*/
/* -- FUNCTIONS -- */
/*-----------------*/
int pwd() {
    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n\n", cwd);
    } else {
        perror("`pwd` error");
    }

    return 0;
}

int printenv() {
    extern char **environ;
    int i = 0;
    while (environ[i]) {
        printf("%s\n", environ[i++]); // prints in form of "variable=value"
    }
    printf("\n");
    return 0;
}

int printenv(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) {

    // TODO: Get environment variable name
    // TODO: Pass it to _getenvvar(envname)
    /*char* result = _getenvvar(envname);
        if(result != NULL) {
            printf("%s\n", result);
        } else {
            printf("\n\n");
        }


    }*/

    printf("ERROR: Builtin command `printenv <args> `not yet implemented\n\n");
    return 0;
}

// TODO: setenv method.
// See: https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html#Environment-Access

int internal_kill(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) {
    int num_args = std::distance(args_begin, args_end);

    if (num_args != 1) {
        printf("USAGE: kill [PID]\n\n");
    } else {
        // Try to convert string into an int
        try {
            pid_t pid = std::stoi(*args_begin, nullptr);
            int retval = kill(pid, SIGTERM);
            if (retval != 0) {
                printf("Couldn't find process with PID %d\n", pid);
            }
        } catch (const std::invalid_argument& ia) {
            printf("USAGE: kill [PID]\n\n");
        }
    }

    return 0;
}

int internal_fg(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) {
    int num_args = std::distance(args_begin, args_end);

    if (num_args != 1) {
        printf("USAGE: fg [PID]\n\n");
    } else {
        // Try to convert string into an int
        try {
            pid_t pid = std::stoi(*args_begin, nullptr);
            int retval = kill(pid, 0);
            if (retval != 0) {
                printf("Couldn't find process with PID %d\n", pid);
            } else {
                // Restore child's ability to write to STDOUT
                kill(pid, SIGALRM);

                // Make the child process part of the shell's group ID again
                // so it can receive signals
                setpgid (pid, getgid());
            }
        } catch (const std::invalid_argument& ia) {
            printf("USAGE: kill [PID]\n\n");
        }
    }

    return 0;
}


int cd(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) {
    int num_args = std::distance(args_begin, args_end);
    int retval = 0;

    // If there is more than 1 argument, just error out
    if (num_args > 1) {
        printf("USAGE: cd [PATH]\n\n");
        return 0;
    } else if (num_args == 0 || *args_begin == std::string("~")) {
        // If there are no arguments or the arg is ~, just go to the user's home
        retval = chdir(ENV_VARS_MAP[std::string("HOME_DIR")].c_str());
    } else if (*args_begin == std::string(".")) {
        retval = 0;
    } else if (*args_begin == std::string("..")) {
        char cwd[MAX_PATH_LENGTH];
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            retval = chdir(dirname(cwd));
        } else {
            retval = -1;
        }
    } else {
        // If the argument is anything else, go to that directory
        retval = chdir((*args_begin).c_str());
    }

    if (retval == -1) {
        perror("`cd` error");
    }

    printf("\n");
    return 0;
}

int processes() {
    /**
     * Print all the running background processes
     */
    Process::print_background_processes();
    return 0;
}

int exit() {
    printf("Goodbye, I'll miss you!\n\n");
    return 1;
}

char* _getenvvar(std::vector<std::string> args);


