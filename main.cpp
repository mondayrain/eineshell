/* Main program for eineshell */
#include <stdlib.h>
#include <stdio.h>
#include "src/environment.h"
#include "src/parser.h"
#include "src/execute.h"

void run_repl_loop();
char* read_input_line();

int main(int argc, char **argv) {
    // SETUP
    set_up_environment();
    // TODO: Read from a config file
    // TODO: Set up signal handler:
    // https://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html#Basic-Signal-Handling
    // https://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c

    // RUN LOOP
    run_repl_loop();

    // RETURN STATUS CODE
    return EXIT_SUCCESS;
}

void run_repl_loop() {
    char* command;
    int exit_called;

    // TODO: How do we handle ctrl-c / ctrl-x / ctrl-z?
    do {
        printf(PROMPT);

        // We assume that the input is a valid one-word command, even though `read_input_line` reads an entire line.
        // TODO: Properly parse input to handle multiple tokens
        command = read_input_line();

        // TODO: For now we're only handling 1-word commands; we want to be
        // able to handle flags, pipes, etc in the future
        exit_called = execute_command(command);
    } while (!exit_called);
}

