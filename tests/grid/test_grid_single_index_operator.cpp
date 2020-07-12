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

TEST(nd_grid, single_index_operator)
{
    {
        nd::grid<int, 3> a({3, 2, 1});
        std::iota(a.begin(), a.end(), 0);

        for (std::size_t i = 0; i < a.num_values(); ++i)
        { EXPECT_EQ(a[i], i); }
    }
    {
        nd::grid<int, 3> a({5, 3, 1});
        a[0] = 4;
        a[1] = 5;
        a[2] = 3;
        a[3] = 7;
        a[4] = 8;
        a[5] = 4;
        a[6] = 7;
        a[7] = 8;
        a[8] = 4;
        a[9] = 3;
        a[10] = 5;
        a[11] = 7;
        a[12] = 2;
        a[13] = 1;
        a[14] = 4;
        EXPECT_EQ(a[0], 4);
        EXPECT_EQ(a[0], a.at_list(0));
        EXPECT_EQ(a[1], 5);
        EXPECT_EQ(a[1], a.at_list(1));
        EXPECT_EQ(a[2], 3);
        EXPECT_EQ(a[2], a.at_list(2));
        EXPECT_EQ(a[3], 7);
        EXPECT_EQ(a[3], a.at_list(3));
        EXPECT_EQ(a[4], 8);
        EXPECT_EQ(a[4], a.at_list(4));
        EXPECT_EQ(a[5], 4);
        EXPECT_EQ(a[5], a.at_list(5));
        EXPECT_EQ(a[6], 7);
        EXPECT_EQ(a[6], a.at_list(6));
        EXPECT_EQ(a[7], 8);
        EXPECT_EQ(a[7], a.at_list(7));
        EXPECT_EQ(a[8], 4);
        EXPECT_EQ(a[8], a.at_list(8));
        EXPECT_EQ(a[9], 3);
        EXPECT_EQ(a[9], a.at_list(9));
        EXPECT_EQ(a[10], 5);
        EXPECT_EQ(a[10], a.at_list(10));
        EXPECT_EQ(a[11], 7);
        EXPECT_EQ(a[11], a.at_list(11));
        EXPECT_EQ(a[12], 2);
        EXPECT_EQ(a[12], a.at_list(12));
        EXPECT_EQ(a[13], 1);
        EXPECT_EQ(a[13], a.at_list(13));
        EXPECT_EQ(a[14], 4);
        EXPECT_EQ(a[14], a.at_list(14));
    }
    {
        nd::grid<int, 2> a({2, 1});
        a[0] = 0;
        a[1] = 1;

        #ifdef ND_DEBUG
        EXPECT_DEATH(a[2] = 0, "");
        #endif

        EXPECT_ANY_THROW(a.at_list(2) = 0);
    }
}
