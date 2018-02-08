#include<stdio.h>

/*-----------------*/
/* -- FUNCTIONS -- */
/*-----------------*/
int pwd() {
    printf("calling environ\n");
    extern char **environ;
    int i = 0;
    while(environ[i]) {
        printf("%s\n", environ[i++]); // prints in form of "variable=value"
    }

    return 0;
}

int cd() {
    printf("calling cd\n");
    return 0;

}

// TODO: setenv method.
// See: https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html#Environment-Access

int printenv() {
    // TODO: By default, environ comes with the PATH
    // inherited from bash. It shouldn't. We need to remove
    // this env var in main upon program startup.

    extern char **environ;
    int i = 0;
    while(environ[i]) {
        printf("%s\n", environ[i++]); // prints in form of "variable=value"
    }
    return 0;
}

int exit() {
    printf("calling exit\n");
    return 1;
}





