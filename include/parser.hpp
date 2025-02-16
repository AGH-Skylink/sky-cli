#ifndef SKYCLI_PARSER_H
#define SKYCLI_PARSER_H

#include "typing.hpp"

#include <string>
#include <sstream>

namespace skycli {

class Parser {
private:
    const char delimeter;
    std::stringstream line;

    bool is_valid_bool(std::string token);

    bool is_valid_int(std::string token);

    bool is_valid_float(std::string token);

    bool is_valid_char(std::string token);

public:
    Parser() : delimeter{' '} {}

    Parser(const char delim) : delimeter(delim) {}

    void load_line(std::string new_line);

    std::string get_next_token(arg_type_t token_type);
};

} // namespace skycli

#endif