#ifndef EINESHELL_ENVIRONMENT_H
#define EINESHELL_ENVIRONMENT_H

#include <map>

extern int MAX_USERNAME_LENGTH;
extern int MAX_PATH_LENGTH;

extern std::map<std::string, std::string> ENV_VARS_MAP;

int set_up_environment(int argc, char** argv);

#endif //EINESHELL_ENVIRONMENT_H
