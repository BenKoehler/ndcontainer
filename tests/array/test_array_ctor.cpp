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

TEST(nd_array, ctor)
{
    {
        [[maybe_unused]] constexpr nd::array<int, 3, 2> a;
        EXPECT_EQ(a.num_dimensions(), 2);

        for (auto x : a.data())
        { EXPECT_EQ(x, 0); }
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 2, 2, 1, 3> a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        EXPECT_EQ(a.num_dimensions(), 4);

        [[maybe_unused]] constexpr nd::array<int, 2, 2, 1, 3> b(a);
        EXPECT_EQ(b.num_dimensions(), 4);

        auto itA = a.data().begin();
        auto itB = b.data().begin();
        for (; itA != a.data().end(); ++itA, ++itB)
        { EXPECT_EQ(*itA, *itB); }
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 1> a(3);
        EXPECT_EQ(a.num_dimensions(), 1);
        EXPECT_EQ(a[0], 3);
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 4> a(9, 8, 7, 6);
        EXPECT_EQ(a.num_dimensions(), 1);
        EXPECT_EQ(a.size(0), 4);
        EXPECT_EQ(a[0], 9);
        EXPECT_EQ(a[1], 8);
        EXPECT_EQ(a[2], 7);
        EXPECT_EQ(a[3], 6);
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 1, 1, 1, 1, 1> a(13);
        EXPECT_EQ(a.num_dimensions(), 5);
        for (auto s : a.size())
        { EXPECT_EQ(s, 1); }
        EXPECT_EQ(a[0], 13);
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 2, 4> a(std::move(nd::array<int, 2, 4>(0, 1, 2, 3, 4, 5, 6, 7)));
        for (std::size_t i = 0; i < a.num_values(); ++i)
        { EXPECT_EQ(a[i], i); }
    }
    {
        [[maybe_unused]] constexpr nd::array<int, 1, 5> a(1, 2, 3, 4, 5);
        [[maybe_unused]] constexpr nd::array<double, 1, 5> b(a);
        EXPECT_EQ(a[0], b[0]);
        EXPECT_EQ(a[1], b[1]);
        EXPECT_EQ(a[2], b[2]);
        EXPECT_EQ(a[3], b[3]);
        EXPECT_EQ(a[4], b[4]);
    }
}
