/* Main program for eineshell */
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include "src/environment.h"
#include "src/parser.h"
#include "src/execute.h"

using std::string;
using std::vector;

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
    string input;
    std::vector<std::string> tokens;
    int exit_called = 0;

    // TODO: Handle ctrl-c / ctrl-x / ctrl-z?
    do {
        print_prompt();
        input = read_input_line();

        if(input.length() > 0) {
            tokens = parse_into_tokens(input);
            exit_called = execute_command(tokens);
        }
    } while (!exit_called);
}

void print_prompt() {
    printf("|%s| %s >> ", ENV_VARS_MAP[std::string("PROMPT")].c_str(), ENV_VARS_MAP[std::string("USERNAME")].c_str());
}

