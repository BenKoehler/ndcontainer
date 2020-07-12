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

TEST(nd_vector, is_valid_ids)
{
    {
        const bool b = nd::vector<int>(3, 2, 4).is_valid_ids(0, 0, 0);
        EXPECT_TRUE(b);
    }
    {
        const bool b = nd::vector<int>(3, 2, 4).is_valid_ids(3, 0, 0);
        EXPECT_FALSE(b);
    }
    {
        const int i[3] = {0, 0, 0};
        const bool b = nd::vector<int>(3, 2, 4).is_valid_ids(i);
        EXPECT_TRUE(b);
    }
    {
        const std::vector i{0, 1, 2, 3};
        bool b = nd::vector<int>(3, 2, 4, 5).is_valid_ids(i.data());
        EXPECT_TRUE(b);
    }
    {
        const int i[1] = {2};
        const bool b = nd::vector<int>(5).is_valid_ids(i);
        EXPECT_TRUE(b);
    }
    {
        const bool b = nd::vector<int>(3, 2, 4).is_valid_ids(std::array<int, 3>{2, 1, 3});
        EXPECT_TRUE(b);
    }
    {
        const bool b = nd::vector<int>(1).is_valid_ids(0);
        EXPECT_TRUE(b);
    }
    {
        const bool b = nd::vector<int>(1).is_valid_ids(1);
        EXPECT_FALSE(b);
    }
    {
        const bool b = nd::vector<int>(1, 1, 1, 1).is_valid_ids(0, 0, 0, 0);
        EXPECT_TRUE(b);
    }
    {
        const bool b = nd::vector<int>(1, 1, 1, 1).is_valid_ids(0, 0, -1, 0);
        EXPECT_FALSE(b);
    }
    {
        const bool b = nd::vector<int>(1, 1, 1, 1).is_valid_ids(0, 0, 0, 1);
        EXPECT_FALSE(b);
    }
}
