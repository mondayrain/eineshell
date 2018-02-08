#ifndef EINESHELL_ENVIRONMENT_H
#define EINESHELL_ENVIRONMENT_H

#include <map>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "environment.h"

int MAX_USERNAME_LENGTH = 64;

#define PROMPT "|EINESHELL|>> "

std::map<std::string, std::string> ENV_VARS_MAP = {
        { std::string("USERNAME"), "" },
        { std::string("HOME_DIR"), "" },
        { std::string("CWD"), "" },
        { std::string("LAST_CWD"), "" }
};

int set_up_environment() {
    int retval = 0;

    // Get username
    char username_buf[MAX_USERNAME_LENGTH];
    retval = getlogin_r(username_buf, MAX_USERNAME_LENGTH);
    if(retval != 0) {
        // TODO: Proper error code
        printf("getlogin_r could not retrieve user; exiting\n");
        return EXIT_FAILURE;
    }

    ENV_VARS_MAP[std::string("USERNAME")] = username_buf;

    // Get the current working directory.
    // By default, POSIX systems set your working directory to the home dir associated with
    // the login account in the user database.


    return 0;
}

#endif //EINESHELL_ENVIRONMENT_H
