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

TEST(nd_array, multi_index_operator)
{
    {
        constexpr nd::array<int, 3, 2, 1> a{0, 1, 2, 3, 4, 5};
        constexpr std::size_t z = 0;

        std::size_t cnt = 0;
        for (std::size_t x = 0; x < a.size(0); ++x)
        {
            for (std::size_t y = 0; y < a.size(1); ++y)
            {
                EXPECT_EQ(a(x, y, z), cnt);
                EXPECT_EQ(a.at_grid(x, y, z), cnt);

                const std::vector v{x, y, z};
                EXPECT_EQ(a(v), cnt);
                EXPECT_EQ(a.at_grid(v), cnt);
                EXPECT_EQ(a(v.data()), cnt);
                EXPECT_EQ(a.at_grid(v.data()), cnt);

                std::size_t p[3] = {x, y, z};
                EXPECT_EQ(a(p), cnt);
                EXPECT_EQ(a.at_grid(p), cnt);

                ++cnt;
            }
        }
    }
    {
        constexpr nd::array<int, 5, 3, 1> a{4, 5, 3, 7, 8, 4, 7, 8, 4, 3, 5, 7, 2, 1, 4};
        EXPECT_EQ(a(0, 0, 0), 4);
        EXPECT_EQ(a.at_grid(0, 0, 0), 4);
        EXPECT_EQ(a(0, 1, 0), 5);
        EXPECT_EQ(a.at_grid(0, 1, 0), 5);
        EXPECT_EQ(a(0, 2, 0), 3);
        EXPECT_EQ(a.at_grid(0, 2, 0), 3);
        EXPECT_EQ(a(1, 0, 0), 7);
        EXPECT_EQ(a.at_grid(1, 0, 0), 7);
        EXPECT_EQ(a(1, 1, 0), 8);
        EXPECT_EQ(a.at_grid(1, 1, 0), 8);
        EXPECT_EQ(a(1, 2, 0), 4);
        EXPECT_EQ(a.at_grid(1, 2, 0), 4);
        EXPECT_EQ(a(2, 0, 0), 7);
        EXPECT_EQ(a.at_grid(2, 0, 0), 7);
        EXPECT_EQ(a(2, 1, 0), 8);
        EXPECT_EQ(a.at_grid(2, 1, 0), 8);
        EXPECT_EQ(a(2, 2, 0), 4);
        EXPECT_EQ(a.at_grid(2, 2, 0), 4);
        EXPECT_EQ(a(3, 0, 0), 3);
        EXPECT_EQ(a.at_grid(3, 0, 0), 3);
        EXPECT_EQ(a(3, 1, 0), 5);
        EXPECT_EQ(a.at_grid(3, 1, 0), 5);
        EXPECT_EQ(a(3, 2, 0), 7);
        EXPECT_EQ(a.at_grid(3, 2, 0), 7);
        EXPECT_EQ(a(4, 0, 0), 2);
        EXPECT_EQ(a.at_grid(4, 0, 0), 2);
        EXPECT_EQ(a(4, 1, 0), 1);
        EXPECT_EQ(a.at_grid(4, 1, 0), 1);
        EXPECT_EQ(a(4, 2, 0), 4);
        EXPECT_EQ(a.at_grid(4, 2, 0), 4);
    }
}
