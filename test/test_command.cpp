#include "../include/command.hpp"

#include <gtest/gtest.h>

using namespace skycli;

class CommandLoadArgumentsTest : public ::testing::TestWithParam<std::tuple<std::string, cmd_error_t>> {
  protected:
    Command cmd;
    std::shared_ptr<Parser> parser_ptr;

    CommandLoadArgumentsTest() {
        parser_ptr = std::make_shared<Parser>();

        std::function<void(BaseArgs *)> f = [](BaseArgs *args){};
        std::vector<arg_type_t> v = {BOOL, BOOL};
        std::shared_ptr<StaticVarHolder> static_vars_ptr = std::make_shared<StaticVarHolder>();

        cmd = {f, v, parser_ptr, static_vars_ptr};
    }
};

TEST_P(CommandLoadArgumentsTest, CorrectExpectedResponse) {
    auto [line, err_code] = GetParam();

    parser_ptr->load_line(line);

    CmdResponse res = cmd.load_arguments();

    ASSERT_EQ(res.error_code, err_code);
};

INSTANTIATE_TEST_CASE_P(
    CommandTests,
    CommandLoadArgumentsTest,
    ::testing::Values(
        std::make_tuple("0 0", NO_ERROR),
        std::make_tuple("0", INSUFFICIENT_ARGS),
        std::make_tuple("0 notbool", WRONG_TYPE_ARG)
    )
);