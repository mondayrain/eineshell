#include <string.h>
#include "execute.h"
#include "builtin.h"


int execute_command(char* command_name) {
/* Returns 1 if the command is exit,
 * and -1 if there was an error.
 * Returns 0 otherwise.
 * */
    if(is_built_in(command_name)) {
        return call_built_in(command_name);
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
    for(int i=0; i < NUM_BUILTINS; i++) {
        if(strcmp(command_name, BUILTINS[i]) == 0) {
            return BUILTIN_FUNCTIONS[i]();
        }
    }

    // Theoretically this should never happen
    return -1;
}

int call(char* command_name) {
    return 0;

}