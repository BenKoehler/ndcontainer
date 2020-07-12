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

TEST(nd_grid, set_values)
{
    {
        nd::grid<double, 1> a({3});
        a.set_values(1, 2, 3);
        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 2);
        EXPECT_EQ(a[2], 3);

        //EXPECT_DEATH(a.set_values(), ""); // expect static assert fail
        #ifdef ND_DEBUG
        EXPECT_DEATH(a.set_values(0,1), "");
        EXPECT_DEATH(a.set_values(0,1,2,3,4), "");
        #endif
    }
    {
        nd::grid<std::string, 2> a({2, 2});
        a.set_values("a", "b", "c", "d");
        EXPECT_EQ(a[0], "a");
        EXPECT_EQ(a[1], "b");
        EXPECT_EQ(a[2], "c");
        EXPECT_EQ(a[3], "d");
        EXPECT_EQ(a(0, 0), "a");
        EXPECT_EQ(a(0, 1), "b");
        EXPECT_EQ(a(1, 0), "c");
        EXPECT_EQ(a(1, 1), "d");
    }
}
