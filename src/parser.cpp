#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_input_line() {
    char *line = NULL;
    size_t bufsize = 0;
    int result = getline(&line, &bufsize, stdin);
    if (result == -1) {
        // TODO: What error to raise when we don't
        // read the line properly? When would this happen?
        exit(1);
    }

    // Remove the newline character
    line[strlen(line)-1] = 0;
    return line;
}

