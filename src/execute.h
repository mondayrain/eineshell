#ifndef EINESHELL_EXECUTE_H
#define EINESHELL_EXECUTE_H

#include <map>
#include <string>
#include <vector>


using std::string;
using std::vector;

extern std::map<pid_t, std::string> PID_MAP;

bool is_built_in(std::string command_name);

int call_built_in(std::string command_name);

int call_built_in_with_args(std::string command_name, std::vector<std::string>::iterator args_begin, std::vector<std::string>::iterator args_end);

int call(std::vector<std::string>);

int execute_command(std::vector<std::string> tokens);

#endif //EINESHELL_EXECUTE_H
