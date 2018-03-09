#include<stdio.h>
#include <unistd.h>
#include<string>
#include<vector>
#include "environment.h"

using std::string;
using std::vector;
using std::distance;

#include<iostream>
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
        // if the argument is .., go up one directory
        // TODO
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

int exit() {
    printf("Goodbye, I'll miss you!\n\n");
    return 1;
}

char* _getenvvar(std::vector<std::string> args);


