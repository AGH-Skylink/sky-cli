#include "../include/parser.hpp"

#include <gtest/gtest.h>

using namespace skycli;

TEST(ParserTests, InitiatedEmpty) {
    Parser parser;

    std::string token = (parser.get_next_token(STRING)).value();

    ASSERT_EQ(token, "");
}

TEST(ParserTests, ReplacesPrevLine) {
    Parser parser;

    parser.load_line("first line");
    parser.load_line("second line");
    std::string token = (parser.get_next_token(STRING)).value();

    ASSERT_EQ(token, "second");
}

TEST(ParserTests, DifferentDelimeter) {
    Parser parser{','};
    parser.load_line("1,2,ala 5,3d");
    std::string token;

    token = (parser.get_next_token(STRING)).value();
    ASSERT_EQ(token, "1");

    token = (parser.get_next_token(STRING)).value();
    ASSERT_EQ(token, "2");

    token = (parser.get_next_token(STRING)).value();
    ASSERT_EQ(token, "ala 5");

    token = (parser.get_next_token(STRING)).value();
    ASSERT_EQ(token, "3d");
}

class ParserCorrectTypesTest : public ::testing::TestWithParam<std::tuple<arg_type_t, std::string, std::vector<std::string>>> {
  protected:
    Parser parser{' '};
};

TEST_P(ParserCorrectTypesTest, AcceptsCorrectType) {
    auto [type, line, correct_tokens] = GetParam();
    size_t token_num = correct_tokens.size();
    parser.load_line(line);

    std::string token;

    for (size_t i = 0; i < token_num; i++) {
        token = (parser.get_next_token(type)).value();
        ASSERT_EQ(token, correct_tokens[i]);
    }
}

INSTANTIATE_TEST_CASE_P(
    ParserTests, 
    ParserCorrectTypesTest, 
    ::testing::Values(
        std::make_tuple(BOOL, "0 1 false true FALSE TRUE", std::vector<std::string>{"0", "1", "false", "true", "FALSE", "TRUE"}),
        std::make_tuple(INT, "0 1 -3 100", std::vector<std::string>{"0", "1", "-3", "100"}),
        std::make_tuple(FLOAT, "1 1.2 1,3 -12.5", std::vector<std::string>{"1", "1.2", "1,3", "-12.5"}),
        std::make_tuple(DOUBLE, "1 1.2 1,3 -12.5", std::vector<std::string>{"1", "1.2", "1,3", "-12.5"}),
        std::make_tuple(CHAR, "0 1 a b", std::vector<std::string>{"0", "1", "a", "b"})
    )
);

class ParserIncorrectTypesTest : public ::testing::TestWithParam<std::tuple<arg_type_t, std::string, size_t>> {
  protected:
    Parser parser{' '};
};

TEST_P(ParserIncorrectTypesTest, RejectsIncorrectType) {
    auto [type, line, token_num] = GetParam();
    parser.load_line(line);

    std::optional<std::string> token;

    for (size_t i = 0; i < token_num; i++) {
        token = parser.get_next_token(type);
        ASSERT_FALSE(token.has_value());
    }
}

INSTANTIATE_TEST_CASE_P(
    ParserTests, 
    ParserIncorrectTypesTest, 
    ::testing::Values(
        std::make_tuple(BOOL, "2 3 aba FALSE2", 4),
        std::make_tuple(INT, "11.2 1a 2,2", 3),
        std::make_tuple(FLOAT, "1.1.1 2,2,2 2.a 2a", 4),
        std::make_tuple(DOUBLE, "1.1.1 2,2,2 2.a 2a", 4),
        std::make_tuple(CHAR, "aa 11 1.", 3)
    )
);