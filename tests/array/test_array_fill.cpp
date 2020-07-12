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

TEST(nd_array, fill)
{
    {
        nd::array<double, 3> a(0, 0, 0);
        for (auto x : a)
        { EXPECT_EQ(x, 0); }

        a.fill(1);
        for (auto x : a)
        { EXPECT_EQ(x, 1); }
    }
    {
        nd::array<double, 6, 4, 2, 6, 76> a;

        a.fill(5);
        for (auto x : a)
        { EXPECT_EQ(x, 5); }

        a.fill(-1);
        for (auto x : a)
        { EXPECT_EQ(x, -1); }
    }
    {
        nd::array<std::string, 5> a("a", "b", "c", "d", "e");

        a.fill("fill");
        for (auto x : a)
        { EXPECT_EQ(x, "fill"); }

        a.fill("");
        for (auto x : a)
        { EXPECT_EQ(x, ""); }
    }
}