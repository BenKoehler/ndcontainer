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

TEST(nd_grid, list_to_grid_id)
{
    {
        nd::grid<int, 3> a({5, 4, 6});

        std::size_t lid = 0;
        for (std::size_t x = 0; x < a.size(0); ++x)
        {
            for (std::size_t y = 0; y < a.size(1); ++y)
            {
                for (std::size_t z = 0; z < a.size(2); ++z)
                {
                    const auto gid = a.list_to_grid_id(lid++);
                    EXPECT_EQ(gid[0], x);
                    EXPECT_EQ(gid[1], y);
                    EXPECT_EQ(gid[2], z);
                }
            }
        }
    }
    {
        nd::grid<int, 3> a({1, 1, 5});

        const auto gid0 = a.list_to_grid_id(0);
        EXPECT_EQ(gid0[0], 0);
        EXPECT_EQ(gid0[1], 0);
        EXPECT_EQ(gid0[2], 0);

        const auto gid1 = a.list_to_grid_id(1);
        EXPECT_EQ(gid1[0], 0);
        EXPECT_EQ(gid1[1], 0);
        EXPECT_EQ(gid1[2], 1);

        const auto gid2 = a.list_to_grid_id(2);
        EXPECT_EQ(gid2[0], 0);
        EXPECT_EQ(gid2[1], 0);
        EXPECT_EQ(gid2[2], 2);

        const auto gid3 = a.list_to_grid_id(3);
        EXPECT_EQ(gid3[0], 0);
        EXPECT_EQ(gid3[1], 0);
        EXPECT_EQ(gid3[2], 3);

        const auto gid4 = a.list_to_grid_id(4);
        EXPECT_EQ(gid4[0], 0);
        EXPECT_EQ(gid4[1], 0);
        EXPECT_EQ(gid4[2], 4);
    }
}
