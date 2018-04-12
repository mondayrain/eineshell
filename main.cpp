/* Main program for eineshell */
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include "src/environment.h"
#include "src/shell.h"
#include "src/parser.h"
#include "src/execute.h"

using std::cout;
using std::string;
using std::vector;

void run_repl_loop();
void print_prompt();

int main(int argc, char **argv) {
    set_up_environment(argc, argv);
    set_up_shell();

    // RUN LOOP
    run_repl_loop();

    // RETURN STATUS CODE
    return EXIT_SUCCESS;
}

void run_repl_loop() {
    std::string input;
    std::vector<std::string> tokens;
    int exit_called = 0;

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
    std::cout << ENV_VARS_MAP[std::string("PROMPT")] << " " << ENV_VARS_MAP[std::string("USERNAME")] << " >> ";
}
