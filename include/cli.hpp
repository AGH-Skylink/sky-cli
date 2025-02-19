#ifndef SKYCLI_CLI_H
#define SKYCLI_CLI_H

#include "command.hpp"
#include "parser.hpp"
#include "static_var_holder.hpp"
#include "help_message.hpp"

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

namespace skycli {

class CLI {
private:
    std::map<std::string, std::unique_ptr<Command>> commands;
    const std::string prompt;
    std::shared_ptr<Parser> parser;
    std::shared_ptr<StaticVarHolder> static_vars;
    std::vector<HelpMessage> help_messages;

    void print_help();

    /** @brief Handle a CmdResponse during runtime
    *
    * Returns true if the response was succesful, false otherwise
    * 
    * @param[in] response the response to handle
    */
    bool handle_cmd_response(CmdResponse response);

public:
    CLI() : prompt{"> "} {
        this->parser = std::make_shared<Parser>();
        this->static_vars = std::make_shared<StaticVarHolder>();
    }

    CLI(const char &delim) : prompt{"> "} {
        this->parser = std::make_shared<Parser>(delim);
        this->static_vars = std::make_shared<StaticVarHolder>();
    }

    CLI(const std::string &prompt_text) : prompt{prompt_text} {
        this->parser = std::make_shared<Parser>();
        this->static_vars = std::make_shared<StaticVarHolder>();
    }

    CLI(const std::string &prompt_text, const char &delim) : prompt{prompt_text} {
        this->parser = std::make_shared<Parser>(delim);
        this->static_vars = std::make_shared<StaticVarHolder>();
    }

    /** @brief Adds a new command to the CLI
    *
    * Maps a function to the given command name.
    * Created Command object is supplied with the type vector.
    * 
    * @param[in] command_name the name which will be mapped to the command
    * @param[in] func function to be called by the command
    * @param[in] type_vec vector of function arguments' types
    */
    void add_command(std::string command_name, std::string description, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec);

    template <typename T>
    void add_static_var(std::string variable_name) {
        static_vars->add_new_var<T>(variable_name);
    }

    /** @brief Run CLI
    *
    * Runs the main loop of the CLI
    * 
    * @param[in] void
    */
    void run_loop();
};

} // namespace skycli

#endif //SKYCLI_CLI_H