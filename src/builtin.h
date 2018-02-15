#ifndef EINESHELL_BUILTIN_H
#define EINESHELL_BUILTIN_H

int pwd();

int cd(const char* argname=NULL);

int printenv(const char* envname=NULL);

int exit();

char* _getenvvar(const char* env_var_name);

const int NUM_BUILTINS = 2;
const char *BUILTINS[] = { "pwd", "exit" };
int (*BUILTIN_FUNCTIONS[])() = { pwd, exit };

const int NUM_BUILTINS_WITH_ARGS = 2;
const char *BUILTINS_WITH_ARGS[] = { "cd", "printenv" };
int (*BUILTIN_FUNCTIONS_WITH_ARGS[])(const char *) = { cd, printenv };

#endif //EINESHELL_BUILTIN_H
