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

TEST(nd_grid, assignment)
{

    nd::grid<double, 1> a({3}, 0.0);
    a[0] = 5;
    a[1] = 6;
    a[2] = 7;

    nd::grid<int, 1> b({3});
    b.fill(1);

    a = b;
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 1);
    EXPECT_EQ(a[2], 1);

    nd::grid<double, 1> c({3});
    c.fill(2);

    a = c;
    EXPECT_EQ(a[0], 2);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 2);

    a = nd::grid<double, 1>({3});
    a[0] = 3;
    a[1] = 2;
    a[2] = 1;
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 1);
}
