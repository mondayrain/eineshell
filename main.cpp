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
static void sig_handler(int signo);

int main(int argc, char **argv) {
    // TODO: Read from a config file
    set_up_environment(argc, argv);

    // RUN LOOP
    run_repl_loop();

    // RETURN STATUS CODE
    return EXIT_SUCCESS;
}

void run_repl_loop() {
    // Signal handling
    // TODO: Why does a child process propogate CTRL-C signals to eineshell? Should not run this if child process is launched.
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

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

static void sig_handler(int signo) {

    switch(signo) {
        case SIGINT:
            printf("\nReceived SIGINT from ctrl-c; terminating shell process\n\n");
            exit(EXIT_SUCCESS);

        // TODO: Handle ctrl-z once job control implemented
    }
}
