/*************************************************************************
	> File Name: main.cpp
	> Author: hug
	> Mail:   hug@haizeix.com
	> Created Time: 二  9/24 18:39:38 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <haizei/test.h>

int add(int a, int b) {
    return a + b;
}

TEST(testFunc, add) {
    EXPECT_EQ(add(5, 3), 8);
    EXPECT_NE(add(5, 3), 9);
    EXPECT_GT(add(6, 7), 10);
    EXPECT_LE(add(6, 7), 13);
    EXPECT_GT(add(6, 7), 20);
}

TEST(testFunc, add2) {
    EXPECT_EQ(add(5, 3), 8);
    EXPECT_EQ(add(5, 3), 9);
    EXPECT_EQ(add(6, 7), 9);
}

int main(int argc, char *argv[]) {
    return RUN_ALL_TESTS();
}
