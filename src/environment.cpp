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
        { std::string("EINESHELL_PATH"), "" }, // TODO: This is a horrible way to do this
        { std::string("USERNAME"), "" },
        { std::string("HOME_DIR"), "" },
        { std::string("CWD"), "" },
        { std::string("LAST_CWD"), "" },
        { std::string("PATH"), "" },
        { std::string("PID"), "" },
        { std::string("PARENT_PID"), "" }
};

int set_up_environment(int argc, char **argv) {
    // Clear environment variables if we need to
    // TODO: This is a horrible way to do this
    ENV_VARS_MAP[std::string("EINESHELL_PATH")] = argv[0];
    // If eineshell was called by another shell, we need to reset the env vars
    if((argc == 2) && !strcmp(argv[1], ENV_VARS_MAP[std::string("EINESHELL_PATH")].c_str())) {
        // clearenv();
    }

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
    // setenv ("PATH", home_dir, 1);

    return 0;
}
