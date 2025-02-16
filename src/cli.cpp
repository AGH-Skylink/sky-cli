#include "cli.hpp"

#include <readline/readline.h>
#include <readline/history.h>

namespace skycli {

void CLI::add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec) {
    this->commands[command_name] = std::make_unique<Command>(func, type_vec, this->parser);
}

} // namespace skycli