#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "helpers.h"

int MAX_COMMAND_TOKEN_LENGTH = 100;

char** parse_input_line(char *input) {
    char *tokens[MAX_COMMAND_TOKEN_LENGTH];
    int num_tokens = split_into_tokens(input, " ", tokens);
    printf("Num of tokens in input '%s': %d\n\n", input, num_tokens);

    char **return_array = (char **) malloc(num_tokens);
    for(int i=0; i < num_tokens; i++) {
        return_array[i] = tokens[i];
    }

    printf("Returning token array with: ");
    for(int i=0; i < num_tokens; i++) {
        printf("%s ", tokens[i]);
    }

    return return_array;
}

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

