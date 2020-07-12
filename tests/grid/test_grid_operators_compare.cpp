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
#include "nd/grid.h"

TEST(nd_grid, operators_compare)
{
    {
        const nd::grid<int, 2> a({3, 2}, 0);
        const nd::grid<int, 2> b({2, 3}, 0);
        const bool eq = a == b;
        const bool neq = a != b;
        //const bool less = a < b; // expect failed compilation
        //const bool less_equal = a <= b; // expect failed compilation
        //const bool greater = a > b; // expect failed compilation
        //const bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
    {
        nd::grid<int, 2> a({2, 3});
        std::iota(a.begin(), a.end(), 0);

        nd::grid<int, 2> b({2, 3});
        for (int i = 0; i < 6; ++i)
        { b[i] = i + 1; }

        const bool eq = a == b;
        const bool neq = a != b;
        const bool less = a < b;
        const bool less_equal = a <= b;
        const bool greater = a > b;
        const bool greater_equal = a >= b;
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
        nd::grid<int, 2> a({1, 1});
        a[0] = 1;
        nd::grid<int, 2> b({1, 1});
        b[0] = 2;
        const bool eq = a == b;
        const bool neq = a != b;
        const bool less = a < b;
        const bool less_equal = a <= b;
        const bool greater = a > b;
        const bool greater_equal = a >= b;
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
        nd::grid<int, 2> a({1, 1});
        a[0] = 3;
        nd::grid<int, 2> b({1, 1});
        b[0] = 3;
        const bool eq = a == b;
        const bool neq = a != b;
        const bool less = a < b;
        const bool less_equal = a <= b;
        const bool greater = a > b;
        const bool greater_equal = a >= b;
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
        nd::grid<int, 2> a({1, 1});
        a[0] = 5;
        nd::grid<double, 2> b({1, 1});
        b[0] = 5.1;
        const bool eq = a == b;
        const bool neq = a != b;
        const bool less = a < b;
        const bool less_equal = a <= b;
        const bool greater = a > b;
        const bool greater_equal = a >= b;
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
        nd::grid<int, 2> a({1, 1});
        a[0] = 5;
        nd::grid<double, 2> b({1, 2});
        b[0] = 5;
        b[1] = 3;
        const bool eq = a == b;
        const bool neq = a != b;
        //const bool less = a < b; // expect failed compilation
        //const bool less_equal = a <= b; // expect failed compilation
        //const bool greater = a > b; // expect failed compilation
        //const bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
    {
        nd::grid<int, 2> a({1, 1});
        a[0] = 5;
        nd::grid<std::string, 2> b({1, 1});
        b[0] = "a";
        const bool eq = a == b;
        const bool neq = a != b;
        //const bool less = a < b; // expect failed compilation
        //const bool less_equal = a <= b; // expect failed compilation
        //const bool greater = a > b; // expect failed compilation
        //const bool greater_equal = a >= b; // expect failed compilation
        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_EQ(eq, !neq);
    }
}
