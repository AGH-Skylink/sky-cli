#ifndef SKYCLI_CLI_H
#define SKYCLI_CLI_H

#include "command.hpp"

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace skycli {

class CLI {
private:
    std::map<std::string, std::unique_ptr<Command>> commands;

public:
    void add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec);
};

} // namespace skycli

#endif //SKYCLI_CLI_H