#ifndef EINESHELL_EXECUTE_H
#define EINESHELL_EXECUTE_H

#include <map>
#include <string>

extern std::map<pid_t, std::string> PID_MAP;

bool is_built_in(char* command_name);

int call_built_in(char* command_name);

int call(char* command_name);

int execute_command(char* command_name);

#endif //EINESHELL_EXECUTE_H
