#include "../include/typing_util.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace skycli;

TEST(TypingUtilTests, ExceptionOnUnknownType) {
    TypingUtil util;

    ASSERT_THROW(util.deduce_type("not_a_type_name"), std::logic_error);
}

class UtilGetTypeStringTest : public ::testing::TestWithParam<std::tuple<arg_type_t, std::string>> {
  protected:
    TypingUtil util;
};

TEST_P(UtilGetTypeStringTest, ReturnsCorrectTypeName) {
    auto [type, name] = GetParam();

    ASSERT_EQ(util.get_type_string(type), name);
}

INSTANTIATE_TEST_CASE_P(
    TypingUtilTests,
    UtilGetTypeStringTest,
    ::testing::Values(
        std::make_tuple(BOOL, "bool"),
        std::make_tuple(INT, "int"),
        std::make_tuple(FLOAT, "float"),
        std::make_tuple(DOUBLE, "double"),
        std::make_tuple(CHAR, "char"),
        std::make_tuple(STRING, "string")
    )
);

class UtilDeduceTypeTest : public ::testing::TestWithParam<std::tuple<arg_type_t, std::string>> {
  protected:
    TypingUtil util;
};

TEST_P(UtilDeduceTypeTest, ReturnsCorrectType) {
    auto [type, name] = GetParam();

    ASSERT_EQ(util.deduce_type(name.c_str()), type);
}

INSTANTIATE_TEST_CASE_P(
    TypingUtilTests,
    UtilDeduceTypeTest,
    ::testing::Values(
        std::make_tuple(BOOL, typeid(bool).name()),
        std::make_tuple(INT, typeid(int).name()),
        std::make_tuple(FLOAT, typeid(float).name()),
        std::make_tuple(DOUBLE, typeid(double).name()),
        std::make_tuple(CHAR, typeid(char).name()),
        std::make_tuple(STRING, typeid(std::string).name())
    )
);