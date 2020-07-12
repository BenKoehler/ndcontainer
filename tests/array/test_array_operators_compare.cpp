/*
 * MIT License
 *
 * Copyright (c) 2018-2020 Benjamin Köhler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "common.h"
#include "nd/array.h"

TEST(nd_array, operators_compare)
{
    {
        constexpr nd::array<int, 3, 2> a;
        constexpr nd::array<int, 2, 3> b;
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        //constexpr bool less = a < b; // expect failed compilation
        //constexpr bool less_equal = a <= b; // expect failed compilation
        //constexpr bool greater = a > b; // expect failed compilation
        //constexpr bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
    {
        constexpr nd::array<int, 2, 3> a{0, 1, 2, 3, 4, 5};
        constexpr nd::array<int, 2, 3> b{1, 2, 3, 4, 5, 6};
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        constexpr bool less = a < b;
        constexpr bool less_equal = a <= b;
        constexpr bool greater = a > b;
        constexpr bool greater_equal = a >= b;
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_TRUE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_FALSE(greater_equal);
        EXPECT_EQ(eq, !neq);
        EXPECT_EQ(less, !greater_equal);
        EXPECT_EQ(less_equal, !greater);
    }
    {
        constexpr nd::array<int, 1, 1> a(1);
        constexpr nd::array<int, 1, 1> b(2);
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        constexpr bool less = a < b;
        constexpr bool less_equal = a <= b;
        constexpr bool greater = a > b;
        constexpr bool greater_equal = a >= b;
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_TRUE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_FALSE(greater_equal);
        EXPECT_EQ(eq, !neq);
        EXPECT_EQ(less, !greater_equal);
        EXPECT_EQ(less_equal, !greater);
    }
    {
        constexpr nd::array<int, 1, 1> a(3);
        constexpr nd::array<int, 1, 1> b(3);
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        constexpr bool less = a < b;
        constexpr bool less_equal = a <= b;
        constexpr bool greater = a > b;
        constexpr bool greater_equal = a >= b;
        EXPECT_TRUE(eq);
        EXPECT_FALSE(neq);
        EXPECT_FALSE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_TRUE(greater_equal);
        EXPECT_EQ(eq, !neq);
        EXPECT_EQ(less, !greater_equal);
        EXPECT_EQ(less_equal, !greater);
    }
    {
        constexpr nd::array<int, 1, 1> a(5);
        constexpr nd::array<double, 1, 1> b(5.1);
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        constexpr bool less = a < b;
        constexpr bool less_equal = a <= b;
        constexpr bool greater = a > b;
        constexpr bool greater_equal = a >= b;
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_TRUE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_FALSE(greater_equal);
        EXPECT_EQ(eq, !neq);
        EXPECT_EQ(less, !greater_equal);
        EXPECT_EQ(less_equal, !greater);
    }
    {
        constexpr nd::array<int, 1, 1> a(5);
        constexpr nd::array<double, 1, 2> b(5, 3);
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        //constexpr bool less = a < b; // expect failed compilation
        //constexpr bool less_equal = a <= b; // expect failed compilation
        //constexpr bool greater = a > b; // expect failed compilation
        //constexpr bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
    {
        nd::array<int, 1, 1> a(5);
        nd::array<std::string, 1, 1> b("a");
        constexpr bool eq = a == b;
        constexpr bool neq = a != b;
        //constexpr bool less = a < b; // expect failed compilation
        //constexpr bool less_equal = a <= b; // expect failed compilation
        //constexpr bool greater = a > b; // expect failed compilation
        //constexpr bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
}
