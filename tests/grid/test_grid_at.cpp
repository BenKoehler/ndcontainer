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

TEST(nd_grid, at)
{
    {
        nd::grid<int, 1> a(3);
        a[0] = 4;
        a[1] = 6;
        a[2] = 8;

        auto x0 = a.at_grid<0>();
        EXPECT_EQ(x0, a[0]);

        auto x1 = a.at_grid<1>();
        EXPECT_EQ(x1, a[1]);

        auto x2 = a.at_grid<2>();
        EXPECT_EQ(x2, a[2]);
    }
    {
        nd::grid<int, 3> a(3, 1, 2);

        for (int i = 0; i < 6; ++i)
        {
            a[i] = i + 1;
        }

        auto x0 = a.at_grid<0, 0, 0>();
        EXPECT_EQ(x0, a[0]);

        auto x1 = a.at_grid<0, 0, 1>();
        EXPECT_EQ(x1, a[1]);

        auto x2 = a.at_grid<2, 0, 1>();
        EXPECT_EQ(x2, a.back());
    }
}
