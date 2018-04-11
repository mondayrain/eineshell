# TODO
- Find out why Ctrl-C kills `eineshell` process along with the child process that it is running
- Clean up local ENV VARs being held
- Return proper error codes for executing non built-in command

- Implement job control (bg and fg commands?)
    - Run a process in the background and keep pid
    - List background processes
    - Bring process back into the foreground

- Implement getenv and setenv builtins
- Handle a bunch of whitespaces in the command (don't assume 1-space delimiters, deal with leading spaces, trailing spaces, extra spaces in between...)
- Find correct ENV VAR for Macbook to ls


- Make eineshell default shell in sshcs
    - Read ENV VARs from file? How does bash get its initial env vars (what launches it and gives it its ENV VARs?)
    - How to permanently change environment variables?
- Get top to work in shell
- Implement command line history using readline as well as movement
- Get tmux to work
