#include<stdio.h>
#include<string>
#include "environment.h"

/*-----------------*/
/* -- FUNCTIONS -- */
/*-----------------*/
int pwd() {
    printf("%s\n\n", ENV_VARS_MAP[std::string("CWD")].c_str());
    return 0;
}

int cd() {
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

int printenv() {
    // TODO: By default, environ comes with the PATH
    // inherited from bash. It shouldn't. We need to remove
    // this env var in main upon program startup.
    // But then if we remove the env vars from each shell process startup,
    // how do we pass the env vars from a parent eineshell to the next?

    extern char **environ;
    int i = 0;
    while(environ[i]) {
        printf("%s\n", environ[i++]); // prints in form of "variable=value"
    }
    printf("\n");
    return 0;
}

int exit() {
    printf("Goodbye, I'll miss you!\n\n");
    return 1;
}





