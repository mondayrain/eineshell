#include<stdio.h>
#include<string>
#include<vector>
#include <stdlib.h>
#include "environment.h"


using std::string;
using std::vector;

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
    printf("%s\n\n", ENV_VARS_MAP[std::string("CWD")].c_str());
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

        return 0;
    }*/

    printf("ERROR: Builtin command `printenv <args> `not yet implemented\n\n");
}

// TODO: setenv method.
// See: https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html#Environment-Access

int cd(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end){
    printf("ERROR: Builtin command `cd` not yet implemented\n\n");
    /*
     * chdir
     * see https://www.gnu.org/software/libc/manual/html_node/Working-Directory.html#Working-Directory
     *
     */
    return 0;

}

int exit() {
    printf("Goodbye, I'll miss you!\n\n");
    return 1;
}

char* _getenvvar(std::vector<std::string> args);


