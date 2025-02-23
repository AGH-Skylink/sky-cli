#include "../include/help_message.hpp"

#include <gtest/gtest.h>
#include <sstream>

using namespace skycli;

class PrintMessageTest : public ::testing::TestWithParam<std::tuple<std::vector<arg_type_t>, std::vector<std::string>>> {
  protected:
    std::stringstream stream;
    std::string line;
};

TEST_P(PrintMessageTest, CorrectMessageByArgCount) {
    auto [types_vec, correct_output] = GetParam();
    
    HelpMessage msg{"test", "test description", types_vec};

    msg.print_message(stream);

    for (size_t i = 0; i < correct_output.size(); i++) {
        std::getline(stream, line, '\n');
        ASSERT_EQ(line, correct_output[i]);
    }
}

INSTANTIATE_TEST_CASE_P(
    HelpMessageTests,
    PrintMessageTest,
    ::testing::Values(
        std::make_tuple(std::vector<arg_type_t>{}, std::vector<std::string>{"test - argument #: 0", "    test description", "--------------------"}),
        std::make_tuple(std::vector<arg_type_t>{INT}, std::vector<std::string>{"test - argument #: 1, argument types: int ", "    test description", "--------------------"}),
        std::make_tuple(std::vector<arg_type_t>{FLOAT, DOUBLE, CHAR, BOOL, STRING}, std::vector<std::string>{"test - argument #: 5, argument types: float double char bool string ", "    test description", "--------------------"})
    )
);