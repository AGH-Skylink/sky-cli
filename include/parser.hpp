#ifndef SKYCLI_PARSER_H
#define SKYCLI_PARSER_H

#include "typing.hpp"

#include <string>
#include <sstream>
#include <optional>

namespace skycli {

class Parser {
private:
    const char delimeter;
    std::stringstream line;

    /** @brief Checks if the string is a valid boolean value 
    *
    * Returns true if the string is equal to "1", "true" or "TRUE".
    * Returns false if the string is equal to "0", "false" or "FALSE".
    * 
    * @param[in] token the string to check
    */
    bool is_valid_bool(const std::string token);

    /** @brief Check if the string is a valid integer value
    *
    * Returns true if the string is only digits, with the exception
    * of a minus sign at the front. Returns false otherwise.
    * 
    * @param[in] token the string to check
    */
    bool is_valid_int(const std::string token);

    /** @brief Check if the string is a valid floating point value
    *
    * Returns true if the string is only digits with a comma/dot as a
    * decimal point, with the exception of a minus sign at the front.
    * Returns false otherwise.
    * 
    * @param[in] token the string to check
    */
    bool is_valid_float(const std::string token);

    /** @brief Check if the string is a valid char
    *
    * Returns true if the string is one character only.
    * Returns false otherwise.
    * 
    * @param[in] token the string to check
    */
    bool is_valid_char(const std::string token);

public:
    Parser() : delimeter{' '} {}

    Parser(const char delim) : delimeter(delim) {}

    /** @brief Load a new line to the parser
    *
    * Clears the current stringstream. Loads the given
    * string to the stream.
    * 
    * @param[in] new_line the string to load
    */
    void load_line(std::string new_line);

    /** @brief Returns next token from the stringstream
    *
    * Returns the next token string from the currently held line
    * with the given type. If there are no more tokens, the function 
    * returns an empty string. If the token is not a valid instance of
    * the given type, the function returns std::nullopt.
    * 
    * @param[in] token the string to check
    */
    std::optional<std::string> get_next_token(arg_type_t token_type);
};

} // namespace skycli

#endif