/* Main program for eineshell */
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "src/environment.h"
#include "src/parser.h"
#include "src/execute.h"

void run_repl_loop();
void print_prompt();

int main(int argc, char **argv) {
    set_up_environment(argc, argv);
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
    int exit_called = 0;

    // TODO: How do we handle ctrl-c / ctrl-x / ctrl-z?
    do {
        print_prompt();

        // We assume that the input is a valid one-word command, even though `read_input_line` reads an entire line.
        // TODO: Properly parse input to handle multiple tokens
        command = read_input_line();

        // TODO: For now we're only handling 1-word commands; we want to be
        // able to handle flags, pipes, etc in the future
        if(strlen(command) > 0) {
            exit_called = execute_command(command);
        }
    } while (!exit_called);
}

void print_prompt() {
    printf("|%s| %s >> ", ENV_VARS_MAP[std::string("PROMPT")].c_str(), ENV_VARS_MAP[std::string("USERNAME")].c_str());
}

