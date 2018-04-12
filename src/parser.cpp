#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "parser.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;

std::string INPUT_DELIMITER = " ";

std::string read_input_line() {
    std::string line;
    std::getline(std::cin, line);
    _trim(line);
    return line;
}

std::vector<std::string> parse_into_tokens(std::string input, std::string delimiter) {
    std::vector<std::string> tokens;
    std::string current_token;

    if(delimiter.empty()) {
        // TODO: Parsing assumes that there will only be one space between arguments
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

// trim from both ends (in place)
void _trim(std::string &s) {
    // Trim whitespace from the right
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());

    // Trim whitespace from the left
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

