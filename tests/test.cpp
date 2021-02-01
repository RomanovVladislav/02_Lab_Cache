//
// Created by vladislav on 29.12.2020.
//

#include <gtest/gtest.h>
#include <Cache.hpp>

TEST(MainTest, 1)
{
    Cache Test1(128,6144);
    Test1.ComplexTest();

    EXPECT_TRUE(true);
}

TEST(MainTest, 2)
{
  Cache Test2(128,6144);
  Test2.ComplexTest();

  EXPECT_TRUE(true);
}
