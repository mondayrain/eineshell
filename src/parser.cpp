#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "parser.h"

using std::string;
using std::vector;
using std::cin;

std::string INPUT_DELIMITER = " ";

std::string read_input_line() {
    // TODO: Trim leading/trailing whitespaces http://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
    std::string line = NULL;
    std::getline(std::cin, line);
    return line;
}

std::vector<std::string> parse_into_tokens(std::string input, std::string delimiter) {
    std::vector<std::string> tokens;
    std::string current_token;

    if(delimiter.empty()) {
        delimiter = INPUT_DELIMITER;
    }

    size_t position = 0;
    while((position = input.find(INPUT_DELIMITER)) != std::string::npos) {
        current_token = input.substr(0, position);
        tokens.push_back(current_token);
        input.erase(0, position + INPUT_DELIMITER.length());
    }

    tokens.push_back(input);

    return tokens;
}
