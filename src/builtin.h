#ifndef EINESHELL_BUILTIN_H
#define EINESHELL_BUILTIN_H

int pwd();

int cd(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end);

int processes();

int internal_kill(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end);

int printenv();

int printenv(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end);

int exit();

char* _getenvvar(std::vector<std::string> args);

std::vector<std::string> BUILTINS { "pwd", "exit", "printenv", "bgproc" };
int (*BUILTIN_FUNCTIONS[])() = { pwd, exit, printenv, processes };

std::vector<std::string> BUILTINS_WITH_ARGS { "cd", "printenv", "kill" };
int (*BUILTIN_FUNCTIONS_WITH_ARGS[])(std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end) = { cd, printenv, internal_kill };

#endif //EINESHELL_BUILTIN_H
