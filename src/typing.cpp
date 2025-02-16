#include "../include/typing.hpp"

#include <typeinfo>
#include <cstring>
#include <string>
#include <stdexcept>

namespace skycli {

arg_type_t deduce_type(const char *type_name) {
    if (strcmp(type_name, typeid(bool).name()) == 0) {
        return BOOL;
    }
    else if (strcmp(type_name, typeid(int).name()) == 0) {
        return INT;
    }
    else if (strcmp(type_name, typeid(float).name()) == 0) {
        return FLOAT;
    }
    else if (strcmp(type_name, typeid(double).name()) == 0) {
        return DOUBLE;
    }
    else if (strcmp(type_name, typeid(char).name()) == 0) {
        return CHAR;
    }
    else if (strcmp(type_name, typeid(std::string).name()) == 0) {
        return STRING;
    }
    else {
        throw std::logic_error("Failed: Unknown parameter type!");
    }
}

}