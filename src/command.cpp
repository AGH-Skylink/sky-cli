#include "../include/command.hpp"

#include <iostream>
#include <optional>

namespace skycli {

std::any Command::convert_to_type(const arg_type_t arg_type, const std::string var) {
    std::any converted;
    
    switch(arg_type) {
        case BOOL:
            if (!var.compare("0") || !var.compare("false") || !var.compare("FALSE")) {
                converted = false;
            }
            else if (!var.compare("1") || !var.compare("true") || !var.compare("TRUE")) {
                converted = true;
            }
            break;
        case INT:
            converted = std::stoi(var);
            break;
        case FLOAT:
            converted = std::stof(var);
            break;
        case DOUBLE:
            converted = std::stod(var);
            break;
        case CHAR:
            converted = *(var.c_str());
            break;
        case STRING:
            converted = var;
            break;
    }

    return converted;
}

std::any& Command::get_arg(const int n) const {
    switch (n) {
        case 0:
            return this->args->_0;
        case 1:
            return this->args->_1;
        case 2:
            return this->args->_2; 
        case 3:
            return this->args->_3;
        case 4:
            return this->args->_4;
        case 5:
            return this->args->_5;
    }

    return this->args->_0;
}

void Command::execute() {
    this->func(this->args.get());
}

} // namespace skycli