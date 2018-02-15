#include<stdio.h>
#include<string>
#include <stdlib.h>
#include "environment.h"


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

int cd(const char* argname=NULL){
    printf("ERROR: Builtin command `cd` not yet implemented\n\n");
    /*
     * chdir
     * see https://www.gnu.org/software/libc/manual/html_node/Working-Directory.html#Working-Directory
     *
     */
    return 0;

}

// TODO: setenv method.
// See: https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html#Environment-Access

int printenv(const char* envname=NULL) {
    if(envname == NULL) {
        extern char **environ;
        int i = 0;
        while (environ[i]) {
            printf("%s\n", environ[i++]); // prints in form of "variable=value"
        }
        printf("\n");
        return 0;
    } else {
        char* result = _getenvvar(envname);
        if(result != NULL) {
            printf("%s\n", result);
        } else {
            printf("\n\n");
        }

        return 0;
    }
}

int exit() {
    printf("Goodbye, I'll miss you!\n\n");
    return 1;
}




