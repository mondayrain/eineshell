/**
 *  Globally accessible information about the shell system itself.
 *
 *  E.g. we must keep track of whether or not the shell
 *  itself is in the foreground/background, etc
 */

#ifndef EINESHELL_SHELL_H
#define EINESHELL_SHELL_H

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

// The file descriptor for the shell
// TODO: Maybe read this from somewhere in the future?
extern int terminal_fd;

// Whether or not the given terminal file descriptor is a terminal (isatty)
extern int terminal_fd_is_tty;

// The currently set pgid that is in the foreground of the terminal
extern pid_t current_foreground_pgid;

// This eineshell's process group ID
extern pid_t eineshell_pgid;

int set_up_shell();

#endif //EINESHELL_SHELL_H
