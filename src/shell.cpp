#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <cstdio>

#include "shell.h"

// TODO: Make Shell a class with static vars instead of having global vars

// We consider the default file descriptor for stdin the fd for the terminal
int terminal_fd = STDIN_FILENO;
int terminal_fd_is_tty;
pid_t current_foreground_pgid;
pid_t eineshell_pgid;

/**
 * Set up the shell.
 *
 * We have to be careful about setting up the shell in case it is
 * invoked from another shell already doing process control.
 *
 */

int set_up_shell() {
    // We check if the file descriptor is an open file descriptor referring to a terminal.
    // At least until we accept a different terminal_fd, this default should never fail.
    terminal_fd_is_tty = isatty(terminal_fd);

    if(terminal_fd_is_tty) {
        /**
         *  * 1) Make sure that eineshell is in the foreground/has been given control of the terminal by
         * the spawning shell. If eineshell is not in the foreground (e.g. was launched as a background job
         * then it needs to stop itself by sending SIGTTIN to its own process group).
         */

        // The process group ID of the _current_ group controlling the terminal (foreground)
        current_foreground_pgid = tcgetpgrp(terminal_fd);
        // The process group ID of this eineshell process
        eineshell_pgid = getpgrp();

        // By convention, a background process that attempts to read
        // or write to the controlling terminal should be sent a SIGTTIN.
        // This stops the process by default.
        while (current_foreground_pgid != eineshell_pgid) {
            // From kill man page: "if pid is negative, but not -1, sig shall be sent to all processes
            // whose process group ID is equal to the absolute value of pid, and for which the process
            // has permission to send a signal. We want to use this in case eineshell was spawned in a job.
            kill(- eineshell_pgid, SIGTTIN);
            current_foreground_pgid = tcgetpgrp(terminal_fd);
            eineshell_pgid = getpgrp();
        }

        /**
         * 2) Once eineshell knows it's in the foreground, it can put itself in the foreground of the terminal!
         */

        // Since eineshell is a child of the spawning process, it needs to put itself in a different
        // process group than the spawning process before putting itself in the foreground.
        // We need to find a random pid number to use, so the next best thing is our own pid
        eineshell_pgid = getpid();
        int retval = setpgid(eineshell_pgid, eineshell_pgid);
        if (retval != 0) {
            perror("Shell couldn't put itself in its own process group before taking control of terminal");
            exit(EXIT_FAILURE);
        }

        // Put its process group in the foreground of the controlling terminal!
        tcsetpgrp(terminal_fd, eineshell_pgid);

        /**
        * 3) Lastly, eineshell needs to ignore all process control signals (e.g. ctrl-C, ctrl-Z) so that it doesn't
        * * stop itself (but can forward these signals to children)! Needs to set action for all stop signals to SIG_IGN.*/
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
        signal (SIGTSTP, SIG_IGN);
        signal (SIGTTIN, SIG_IGN);
        signal (SIGTTOU, SIG_IGN);
        signal (SIGCHLD, SIG_IGN);

        // Successfully set up shell!
        return 0;
    } else {
        return -1;
    }
}