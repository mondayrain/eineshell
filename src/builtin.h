#ifndef EINESHELL_BUILTIN_H
#define EINESHELL_BUILTIN_H

int pwd();

int cd();

int printenv();

int exit();

const int NUM_BUILTINS = 4;
const char *BUILTINS[] = { "pwd", "cd", "printenv", "exit" };
int (*BUILTIN_FUNCTIONS[])() = { pwd, cd, printenv, exit };

#endif //EINESHELL_BUILTIN_H
