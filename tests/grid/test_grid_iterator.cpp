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

TEST(nd_grid, iterator)
{
    {
        nd::grid<double, 1> a(3);
        a[0] = 1.1;
        a[1] = 2.2;
        a[2] = 3.3;

        {
            auto it = a.begin();
            std::size_t i = 0;

            for (; it != a.end(); ++i, ++it)
            {
                EXPECT_EQ(a[i], *it);
                const auto gid = a.list_to_grid_id(i);
                EXPECT_EQ(gid[0], i);
            }
        }
        {
            auto it = a.rbegin();
            std::size_t i = a.num_values() - 1;

            for (; it != a.rend(); --i, ++it)
            {
                EXPECT_EQ(a[i], *it);
                const auto gid = a.list_to_grid_id(i);
                EXPECT_EQ(gid[0], i);
            }
        }
    }
    {
        nd::grid<int, 2> a(3, 2);
        // col0
        a[0] = 2;
        a[1] = 3;
        a[2] = 4;
        // col1
        a[3] = 5;
        a[4] = 6;
        a[5] = 7;

        auto it = a.begin();

        EXPECT_EQ(*it, 2);
        ++it;

        EXPECT_EQ(*it, 3);
        ++it;

        EXPECT_EQ(*it, 4);
        ++it;

        EXPECT_EQ(*it, 5);
        ++it;

        EXPECT_EQ(*it, 6);
        ++it;

        EXPECT_EQ(*it, 7);
        //++it;
    }
}