#include "../include/parser.hpp"

namespace skycli {

void Parser::load_line(std::string new_line) {
    if (!new_line.empty())
        this->line.clear();
        this->line << new_line;
}

}