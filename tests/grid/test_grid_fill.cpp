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

TEST(nd_grid, fill)
{
    {
        nd::grid<double, 1> a({3});
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
        for (auto x : a)
        { EXPECT_EQ(x, 0); }

        a.fill(1);
        for (auto x : a)
        { EXPECT_EQ(x, 1); }
    }
    {
        nd::grid<double, 5> a({6, 4, 2, 6, 76});

        a.fill(5);
        for (auto x : a)
        { EXPECT_EQ(x, 5); }

        a.fill(-1);
        for (auto x : a)
        { EXPECT_EQ(x, -1); }
    }
    {
        nd::grid<std::string, 1> a({5});
        a[0] = "a";
        a[1] = "b";
        a[2] = "c";
        a[3] = "d";
        a[4] = "e";

        a.fill("fill");
        for (auto x : a)
        { EXPECT_EQ(x, "fill"); }

        a.fill("");
        for (auto x : a)
        { EXPECT_EQ(x, ""); }
    }
}