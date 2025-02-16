#include "cli.hpp"

namespace skycli {

void CLI::add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec) {
    commands[command_name] = std::make_unique<Command>(func, type_vec);
}    

} // namespace skycli