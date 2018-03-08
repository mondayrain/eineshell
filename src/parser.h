#ifndef EINESHELL_PARSER_H
#define EINESHELL_PARSER_H

std::string read_input_line();

std::vector<std::string> parse_into_tokens(std::string input, std::string delimiter = "");

#endif //EINESHELL_PARSER_H
