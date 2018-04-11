# TODO
- Implement job control (bg and fg commands?)
    - Run a process in the background and keep pid
    - List background processes
    - Bring process back into the foreground

- Fix handling of Ctrl-C (only kill eineshell if no foreground child processes)
- Implement Ctrl-Z

- Implement getenv and setenv builtins
- Find correct ENV VAR for Macbook to ls

- Make eineshell default shell in sshcs
    - Read ENV VARs from file? How does bash get its initial env vars (what launches it and gives it its ENV VARs?)
    - How to permanently change environment variables?
- Get top to work in shell
- Implement command line history using readline as well as movement
- Get tmux to work
