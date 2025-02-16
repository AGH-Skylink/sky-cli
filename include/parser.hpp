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

public:
    Parser() : delimeter{' '} {}

    Parser(const char delim) : delimeter(delim) {}

    void load_line(std::string new_line);
};

} // namespace skycli

#endif