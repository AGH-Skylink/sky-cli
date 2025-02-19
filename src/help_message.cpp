#include "../include/help_message.hpp"

#include <iostream>

namespace skycli {

void HelpMessage::print_message() {
    TypingUtil util;

    std::cout << this->name << " - ";
    std::cout << "argument #: " << this->arg_count;

    if (this->arg_count > 0) {
        std::cout << ", argument types: ";

        for (auto a : this->arg_types) {
            std::cout << util.get_type_string(a) << " ";
        }
    }

    std::cout << std::endl;
    std::cout << "    " << description << std::endl;
    std::cout << "--------------------" << std::endl;
}

} // namespace skycli