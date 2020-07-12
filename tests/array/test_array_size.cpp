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

TEST(nd_array, size)
{
    {
        constexpr nd::array<int, 3, 2> a;
        EXPECT_FALSE(a.empty());
        EXPECT_EQ(a.num_values(), 6);

        constexpr std::array<int, a.num_values()> avals{a[0], a[1], a[2], a[3], a[4], a[5]};
        EXPECT_EQ(avals[0], 0);
        EXPECT_EQ(avals[1], 0);
        EXPECT_EQ(avals[2], 0);
        EXPECT_EQ(avals[3], 0);
        EXPECT_EQ(avals[4], 0);
        EXPECT_EQ(avals[5], 0);

        constexpr auto x = a.size(0);
        constexpr auto y = a.size(1);
        EXPECT_EQ(x, 3);
        EXPECT_EQ(y, 2);

        constexpr auto dims = a.num_dimensions();
        EXPECT_EQ(dims, 2);
        constexpr auto dims2 = decltype(a)::num_dimensions();
        EXPECT_EQ(dims, dims2);

        constexpr auto size = a.size();
        EXPECT_EQ(x, size[0]);
        EXPECT_EQ(y, size[1]);
        EXPECT_EQ(size.size(), 2);
    }
}
