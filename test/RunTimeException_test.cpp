#include "../src/config/RunTimeException.hpp"
#include "gtest/gtest.h"

TEST(RunTimeExceptionTest, ConstructorEndToken) {
    Token            token(END, "", 1);
    RunTimeException exception(token, "Unexpected end of file");

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 1] at end: Unexpected end of file");
}

TEST(RunTimeExceptionTest, ConstructorOtherToken) {
    Token            token(SERVER, "server", 2);
    RunTimeException exception(token, "Unexpected token");

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 2] at 'server': Unexpected token");
}

TEST(RunTimeExceptionTest, What) {
    Token            token(SERVER, "server", 2);
    RunTimeException exception(token, "Unexpected token");

    // Check if the what function correctly returns the error message
    EXPECT_STREQ(exception.what(), "[line 2] at 'server': Unexpected token");
}
