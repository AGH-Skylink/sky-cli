#ifndef SKYCLI_COMMAND_H
#define SKYCLI_COMMAND_H

#include "typing_util.hpp"
#include "parser.hpp"
#include "static_var_holder.hpp"

#include <functional>
#include <any>
#include <memory>

namespace skycli 
{

struct BaseArgs {
    std::any _0;
    std::any _1;
    std::any _2;
    std::any _3;
    std::any _4;
    std::any _5;
    std::shared_ptr<StaticVarHolder> static_vars;
};

enum cmd_error_t {
    NO_ERROR = 0,
    INSUFFICIENT_ARGS = -1,
    WRONG_TYPE_ARG = -2,
};

struct CmdResponse {
    cmd_error_t error_code;
    size_t error_arg_num;
    size_t arg_count;
    arg_type_t arg_type;
};

class Command {
private:
    std::function<void(BaseArgs *)> func;
    std::unique_ptr<BaseArgs> args;
    size_t arg_count;
    std::vector<arg_type_t> arg_types;
    std::shared_ptr<Parser> parser;

    /** @brief Converts a string to given type
    *
    * Converts the string to a type given by arg_type.
    * Returns an std::any object.
    * 
    * @param[in] arg_type result type
    * @param[in] var string to convert 
    */
    std::any convert_to_type(const arg_type_t arg_type, const std::string var);

public:
    Command() {
        this->args = std::make_unique<BaseArgs>();
        this->arg_count = 0;
    }

    Command(std::function<void(BaseArgs *)> f, std::vector<arg_type_t> v, std::shared_ptr<Parser> parser_ptr, std::shared_ptr<StaticVarHolder> static_vars_ptr) {
        this->func = f;
        this->args = std::make_unique<BaseArgs>();
        this->arg_types = v;
        this->arg_count = v.size();
        this->parser = parser_ptr;
        this->args->static_vars = static_vars_ptr;
    }

    Command &operator=(const Command& other) {
        this->func = other.func;
        this->arg_count = other.arg_count;
        this->arg_types = other.arg_types;
        this->parser = other.parser;

        this->args->static_vars = other.args->static_vars;

        for (size_t i = 0; i < this->arg_count; i++) {
            this->get_arg(i) = other.get_arg(i);
        }

        return *this;
    }

    /** @brief Get access to an args member
    *
    * Returns a reference to the specified args member
    * 
    * @param[in] i the args' number
    */
    std::any &get_arg(const int i) const;

    /** @brief Load arguments into args
    *
    * Loads and checks argument tokens with the parser.
    * Returns CmdResponse. In the case of an argument of a wrong time, 
    * the responses error code is WRONG_TYPE_ARG. If there were not enough 
    * arguments given, it returns with a INSUFFICIENT_ARGS error code.
    * 
    * @param[in] void
    */
    CmdResponse load_arguments();
    
    /** @brief Execute the function
    * 
    * Executes the function with currently held arguments
    * 
    * @param[in] void
    */
    void execute();
};

} // namespace skycli

#endif //SKYCLI_COMMAND_H