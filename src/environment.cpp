#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <cstring>
#include <string>
#include <unistd.h>

int MAX_USERNAME_LENGTH = 64;
int MAX_PATH_LENGTH = 255;

// TODO: Clean this up, we don't need a bunch of these
std::map<std::string, std::string> ENV_VARS_MAP = {
        { std::string("PROMPT"), "|EINESHELL|" },
        { std::string("USERNAME"), "" },
        { std::string("HOME_DIR"), "" },
        { std::string("PATH"), "" } // Currently unused
};

int set_up_environment(int argc, char **argv) {
    // TODO: Need to read from a config file if eineshell is being run as the default terminal

    // Get username
    int retval = 0;

    char username_buf[MAX_USERNAME_LENGTH];
    retval = getlogin_r(username_buf, MAX_USERNAME_LENGTH);
    if(retval != 0) {
        // TODO: Proper error code
        printf("getlogin_r could not retrieve user; exiting\n");
        return EXIT_FAILURE;
    }
    ENV_VARS_MAP[std::string("USERNAME")] = username_buf;

    // Get the home directory/current working directory.
    // By default, POSIX systems set your working directory to the home dir associated with
    // the login account in the user database.
    struct passwd *user_info = getpwnam(username_buf);
    char *home_dir = user_info->pw_dir;

    // Update our local env vars for easy use
    ENV_VARS_MAP[std::string("HOME_DIR")] = home_dir;


    // Set env vars on actual system
    setenv("HOME", home_dir, 1);
    setenv("PWD", home_dir, 1);
    setenv("LOGNAME", username_buf, 1);

    // TODO: We currently inherit the path from the process that spawns us (i.e. bash)
    // We need to set the path based on a config file if we set eineshell to be the default terminal
    // setenv ("PATH", home_dir, 1);

    return 0;
}
