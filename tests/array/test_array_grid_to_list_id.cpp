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

TEST(nd_array, grid_to_list_id)
{
    {
        constexpr nd::array<int, 5, 4, 6> a;

        std::size_t cnt = 0;
        for (std::size_t x = 0; x < a.size(0); ++x)
        {
            for (std::size_t y = 0; y < a.size(1); ++y)
            {
                for (std::size_t z = 0; z < a.size(2); ++z)
                {
                    {
                        const auto lid = a.grid_to_list_id(x, y, z);
                        EXPECT_EQ(lid, cnt);
                    }
                    {
                        const auto lid = a.grid_to_list_id(std::array<int, 3>{static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)});
                        EXPECT_EQ(lid, cnt);
                    }
                    {
                        const auto lid = a.grid_to_list_id(std::vector{x, y, z});
                        EXPECT_EQ(lid, cnt);
                    }

                    ++cnt;
                }
            }
        }
    }
    {
        constexpr nd::array<int, 1, 2, 4> a;

        constexpr auto lid0 = a.grid_to_list_id(0, 0, 0);
        EXPECT_EQ(lid0, 0);

        constexpr auto lid1 = a.grid_to_list_id(0, 0, 1);
        EXPECT_EQ(lid1, 1);

        constexpr auto lid2 = a.grid_to_list_id(0, 0, 2);
        EXPECT_EQ(lid2, 2);

        constexpr auto lid3 = a.grid_to_list_id(0, 0, 3);
        EXPECT_EQ(lid3, 3);

        constexpr auto lid4 = a.grid_to_list_id(0, 1, 0);
        EXPECT_EQ(lid4, 4);

        constexpr auto lid5 = a.grid_to_list_id(0, 1, 1);
        EXPECT_EQ(lid5, 5);

        constexpr auto lid6 = a.grid_to_list_id(0, 1, 2);
        EXPECT_EQ(lid6, 6);

        constexpr auto lid7 = a.grid_to_list_id(0, 1, 3);
        EXPECT_EQ(lid7, 7);
    }
}
