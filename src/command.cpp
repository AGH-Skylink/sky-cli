#include "../include/command.hpp"

namespace skycli {

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