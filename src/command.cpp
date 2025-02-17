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

CmdResponse Command::load_arguments() {
    std::optional<std::string> token;

    for (size_t i = 0; i < this->arg_count; i++) {
        token = parser->get_next_token(arg_types[i]);

        if (!token.has_value()) {
            return CmdResponse{WRONG_TYPE_ARG, i, this->arg_count, arg_types[i]};
        }

        if (token.value().empty()) {
            return CmdResponse{INSUFFICIENT_ARGS, i, this->arg_count, arg_types[i]};
        }

        get_arg(i) = this->convert_to_type(arg_types[i], token.value());
    }

    return CmdResponse{NO_ERROR};
}

void Command::execute() {
    this->func(this->args.get());
}

} // namespace skycli