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

TEST(nd_array, swap)
{
    { // swap with same value_type
        nd::array<int, 3, 2> a;
        EXPECT_EQ(a[0], 0);
        EXPECT_EQ(a[1], 0);
        EXPECT_EQ(a[2], 0);
        EXPECT_EQ(a[3], 0);
        EXPECT_EQ(a[4], 0);
        EXPECT_EQ(a[5], 0);

        nd::array<int, 3, 2> b(3, 4, 5, 6, 7, 8);
        EXPECT_EQ(b[0], 3);
        EXPECT_EQ(b[1], 4);
        EXPECT_EQ(b[2], 5);
        EXPECT_EQ(b[3], 6);
        EXPECT_EQ(b[4], 7);
        EXPECT_EQ(b[5], 8);

        a.swap(std::move(b));

        EXPECT_EQ(a[0], 3);
        EXPECT_EQ(a[1], 4);
        EXPECT_EQ(a[2], 5);
        EXPECT_EQ(a[3], 6);
        EXPECT_EQ(a[4], 7);
        EXPECT_EQ(a[5], 8);

        EXPECT_EQ(b[0], 0);
        EXPECT_EQ(b[1], 0);
        EXPECT_EQ(b[2], 0);
        EXPECT_EQ(b[3], 0);
        EXPECT_EQ(b[4], 0);
        EXPECT_EQ(b[5], 0);
    }
    { // swap with different value_type
        nd::array<int, 2, 3> a{0, 0, 0, 0, 0, 0};
        EXPECT_EQ(a[0], 0);
        EXPECT_EQ(a[1], 0);
        EXPECT_EQ(a[2], 0);
        EXPECT_EQ(a[3], 0);
        EXPECT_EQ(a[4], 0);
        EXPECT_EQ(a[5], 0);

        nd::array<double, 2, 3> b{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        EXPECT_EQ(b[0], 1);
        EXPECT_EQ(b[1], 2);
        EXPECT_EQ(b[2], 3);
        EXPECT_EQ(b[3], 4);
        EXPECT_EQ(b[4], 5);
        EXPECT_EQ(b[5], 6);

        a.swap(b);

        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 2);
        EXPECT_EQ(a[2], 3);
        EXPECT_EQ(a[3], 4);
        EXPECT_EQ(a[4], 5);
        EXPECT_EQ(a[5], 6);

        EXPECT_EQ(b[0], 0.0);
        EXPECT_EQ(b[1], 0.0);
        EXPECT_EQ(b[2], 0.0);
        EXPECT_EQ(b[3], 0.0);
        EXPECT_EQ(b[4], 0.0);
        EXPECT_EQ(b[5], 0.0);
    }
    {
        nd::array<int, 1, 2> a(0, 0);
        nd::array<int, 1, 2> b(1, 1);
        a.swap(std::move(b));
        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 1);
    }
    {
        nd::array<int, 1, 2> a(0, 0);
        nd::array<double, 1, 2> b(1.0, 2.0);
        a.swap(std::move(b));
        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 2);
    }
}
