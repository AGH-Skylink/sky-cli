#include "../include/help_message.hpp"

#include <iostream>

namespace skycli {

void HelpMessage::print_message(std::ostream &stream) {
    TypingUtil util;

    stream << this->name << " - ";
    stream << "argument #: " << this->arg_count;

    if (this->arg_count > 0) {
        stream << ", argument types: ";

        for (auto a : this->arg_types) {
            stream << util.get_type_string(a) << " ";
        }
    }

    stream << std::endl;
    stream << "    " << description << std::endl;
    stream << "--------------------" << std::endl;
}

} // namespace skycli