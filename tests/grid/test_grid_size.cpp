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

TEST(nd_grid, size)
{
    {
        nd::grid<int, 2> a({3, 2}, 0);
        EXPECT_FALSE(a.empty());
        EXPECT_EQ(a.num_values(), 6);

        std::vector<int> avals(a.num_values());
        avals[0] = a[0];
        avals[1] = a[1];
        avals[2] = a[2];
        avals[3] = a[3];
        avals[4] = a[4];
        avals[5] = a[5];
        EXPECT_EQ(avals[0], 0);
        EXPECT_EQ(avals[1], 0);
        EXPECT_EQ(avals[2], 0);
        EXPECT_EQ(avals[3], 0);
        EXPECT_EQ(avals[4], 0);
        EXPECT_EQ(avals[5], 0);

        auto x = a.size(0);
        auto y = a.size(1);
        EXPECT_EQ(x, 3);
        EXPECT_EQ(y, 2);

        auto dims = a.num_dimensions();
        EXPECT_EQ(dims, 2);

        auto size = a.size();
        EXPECT_EQ(x, size[0]);
        EXPECT_EQ(y, size[1]);
        EXPECT_EQ(size.size(), 2);
    }
}
