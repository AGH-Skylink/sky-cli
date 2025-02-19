#ifndef SKYCLI_HELP_MESSAGE_H
#define SKYCLI_HELP_MESSAGE_H

#include "typing.hpp"

#include <string>
#include <vector>

namespace skycli {

class HelpMessage {
private:
    const std::string name;
    const size_t arg_count;
    const std::vector<arg_type_t> arg_types;
    const std::string description;

public:
    HelpMessage() = default;

    HelpMessage(std::string cmd_name, std::string desc, std::vector<arg_type_t> type_vec) 
        : name{cmd_name}, 
        arg_types{type_vec}, 
        arg_count{type_vec.size()}, 
        description{desc} {}

    void print_message();
};

} // namespace skycli

#endif //SKYCLI_HELP_MESSAGE_H