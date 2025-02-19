#ifndef SKYCLI_WRAPPER_MACROS_H
#define SKYCLI_WRAPPER_MACROS_H

#include "typing.hpp"

#define CONCAT(i) add_command_to_cli_ ## i

#define CONCAT_S(i) add_command_to_cli_s_ ## i

#define COUNT_VARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define COUNT_VARGS(...) COUNT_VARGS_IMPL(_, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define add_command_to_cli_0(cli_obj, command_name, func) { \
std::vector<skycli::arg_type_t> vec = {}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_0(cli_obj, command_name, func) { \
std::vector<skycli::arg_type_t> vec = {}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get()); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_1(cli_obj, command_name, func, type1) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_1(cli_obj, command_name, func, type1) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_2(cli_obj, command_name, func, uses_static, type1, type2) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_2(cli_obj, command_name, func, type1, type2) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_3(cli_obj, command_name, func, type1, type2, type3) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_3(cli_obj, command_name, func, type1, type2, type3) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_4(cli_obj, command_name, func, type1, type2, type3, type4) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_4(cli_obj, command_name, func, type1, type2, type3, type4) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_5(cli_obj, command_name, func, type1, type2, type3, type4, type5) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_s_5(cli_obj, command_name, func, type1, type2, type3, type4, type5) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_6(cli_obj, command_name, func, type1, type2, type3, type4, type5, type6) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name()), skycli::deduce_type(typeid(type6).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4), std::any_cast<type6>(args->_5)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_6(cli_obj, command_name, func, type1, type2, type3, type4, type5, type6) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name()), skycli::deduce_type(typeid(type6).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(args->static_vars.get(), std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4), std::any_cast<type6>(args->_5)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_impl(cli_obj, command_name, func, number_of_args, ...) \
CONCAT(number_of_args) (cli_obj, command_name, func, __VA_ARGS__)

#define add_command_to_cli_s_impl(cli_obj, command_name, func, number_of_args, ...) \
CONCAT_S(number_of_args) (cli_obj, command_name, func, __VA_ARGS__)

/** @brief Adds a command to a CLI 
*
* Macro for automatic wrapping and adding commands to CLI.
* Adds a command invoked by command_name to the CLI.
* The command executes the provided function func with 
* the parameters provided in the CLI. 
* 
* @param[in] cli_obj name of an existing CLI object
* @param[in] command_name name of the new command
* @param[in] func underlying function for the command
* @param[in] ... func arguments' types
*/
#define add_command_to_cli(cli_obj, command_name, func, ...) \
add_command_to_cli_impl(cli_obj, command_name, func, COUNT_VARGS(__VA_ARGS__), __VA_ARGS__)

/** @brief Adds a command to a CLI 
*
* Macro for automatic wrapping and adding commands to CLI.
* Adds a command invoked by command_name to the CLI.
* The command executes the provided function func with 
* the parameters provided in the CLI. Includes static variables
* inside of the CLI.
* 
* @param[in] cli_obj name of an existing CLI object
* @param[in] command_name name of the new command
* @param[in] func underlying function for the command
* @param[in] ... func arguments' types
*/
#define add_command_to_cli_s(cli_obj, command_name, func, ...) \
add_command_to_cli_s_impl(cli_obj, command_name, func, COUNT_VARGS(__VA_ARGS__), __VA_ARGS__)

#endif //SKYCLI_WRAPPER_MACROS_H