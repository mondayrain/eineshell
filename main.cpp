/* Main program for eineshell */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include "src/environment.h"
#include "src/parser.h"
#include "src/execute.h"

using std::cout;
using std::string;
using std::vector;

void run_repl_loop();
void print_prompt();
void sig_handler(int signo);

/* Signal handling:
 * int SIGTERM - The SIGTERM signal is a generic signal used to cause program termination.
        The shell command kill generates SIGTERM by default.
 int SIGQUIT - similar to SIGINT, except that it’s controlled by a different key—the QUIT character, usually C-\—and produces a core dump when it terminates the process
*/

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
    if (signal (SIGINT, sig_handler) == SIG_IGN) {
        signal (SIGINT, SIG_IGN);
    }

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

void sig_handler(int signo) {
    // TODO: Handle ctrl-x / ctrl-z?

    if (signo == SIGINT) {
        printf("\nReceived SIGINT from ctrl-c; terminating shell process\n\n");
        exit(EXIT_SUCCESS);
    }
}
