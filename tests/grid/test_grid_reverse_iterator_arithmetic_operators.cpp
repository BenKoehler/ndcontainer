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

TEST(nd_grid, reverse_iterator_arithmetic_operators)
{
    {
        nd::grid<int, 2> a({2, 3});
        for (int i = 0; i < 6; ++i)
        {
            a[i] = i + 1;
        }

        auto it = a.rbegin();

        EXPECT_EQ(*it, 6);
        EXPECT_EQ(*(it + 1), 5);
        EXPECT_EQ(*(it + 2), 4);
        it += 3;
        EXPECT_EQ(*it, 3);
        EXPECT_EQ(*(it + 1), 2);
        EXPECT_EQ(*(it + 2), 1);
        it = 3 + it;
        EXPECT_EQ(it, a.rend());
        ++it;
        it += 1;
        it -= 2;
        --it;
        EXPECT_EQ(*it, 1);

        *it = 6;
        EXPECT_EQ(*it, 6);
        EXPECT_EQ(a[0], 6);

        EXPECT_EQ(std::distance(a.rbegin(), a.rend()), 6);
    }
    {
        nd::grid<int, 2> a({2, 3});
        for (int i = 0; i < 6; ++i)
        {
            a[i] = i + 1;
        }

        auto it = static_cast<const nd::grid<int, 2>&>(a).rbegin();

        EXPECT_EQ(*it, 6);
        EXPECT_EQ(*(it + 1), 5);
        EXPECT_EQ(*(it + 2), 4);
        it += 3;
        EXPECT_EQ(*it, 3);
        EXPECT_EQ(*(it + 1), 2);
        EXPECT_EQ(*(it + 2), 1);
        it = 3 + it;
        EXPECT_EQ(it, a.rend());
        ++it;
        it += 1;
        it -= 2;
        --it;
        EXPECT_EQ(*it, 1);

        EXPECT_EQ(std::distance(static_cast<const nd::grid<int, 2>&>(a).rbegin(), static_cast<const nd::grid<int, 2>&>(a).rend()), 6);
    }
}
