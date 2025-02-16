#include "../include/parser.hpp"

#include <algorithm>

namespace skycli {

void Parser::load_line(std::string new_line) {
    if (!new_line.empty())
        this->line.clear();
        this->line << new_line;
}

bool Parser::is_valid_bool(std::string token) {
    if (!token.compare("0") || !token.compare("1") || !token.compare("true") || !token.compare("false") || !token.compare("TRUE") || !token.compare("FALSE"))
        return true;
    else 
        return false;
}

bool Parser::is_valid_int(std::string token) {
    if (token.at(0) == '-') {
        token.erase(0);
    }

    if (token.find_first_not_of("0123456789") == std::string::npos)
        return true;
    else
        return false;
}

bool Parser::is_valid_float(std::string token) {
    if (token.at(0) == '-') {
        token.erase(0);
    }
    
    if (token.find_first_not_of("0123456789.,") == std::string::npos) {
        if (token.find('.') != std::string::npos) {
            if (std::count(token.begin(), token.end(), '.') > 1) return false;
        }
        else if (token.find(',') != std::string::npos) {
            if (std::count(token.begin(), token.end(), ',') > 1) return false;
        }
        else return true;

        if (token.find('.') == std::string::npos && token.find(',') == std::string::npos) return false;

        return true;
    }
    else {
        return false;
    }
}

bool Parser::is_valid_char(std::string token) {
    return token.length() == 1;
}

}