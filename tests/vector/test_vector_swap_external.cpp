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
#include "nd/vector.h"

TEST(nd_vector, swap_external)
{
    {
        nd::vector<int> a(1, 2);
        a.fill(0);
        nd::vector<int> b(1, 2);
        b.fill(1);
        swap(a, b);
        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 1);
        EXPECT_EQ(b[0], 0);
        EXPECT_EQ(b[1], 0);
    }
    {
        nd::vector<int> a(1, 2);
        a.fill(0);
        nd::vector<int> b(1, 2);
        b.fill(1);
        swap(std::move(a), b);
        EXPECT_EQ(b[0], 0);
        EXPECT_EQ(b[1], 0);
        EXPECT_TRUE(a.empty());
    }
    {
        nd::vector<int> a(1, 2);
        a.fill(0);
        nd::vector<double> b(1, 2);
        b.fill(1);
        swap(a, std::move(b));
        EXPECT_EQ(a[0], 1);
        EXPECT_EQ(a[1], 1);
    }
}