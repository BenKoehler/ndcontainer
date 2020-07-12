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

TEST(nd_vector, stride)
{
    {
        std::vector<int> s(7);
        s[0] = 6;
        s[1] = 5;
        s[2] = 4;
        s[3] = 3;
        s[4] = 2;
        s[5] = 1;
        s[6] = 100;

        const nd::vector<int> a(s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
        EXPECT_EQ(a.stride(0), s[1] * s[2] * s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(a.stride(1), s[2] * s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(a.stride(2), s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(a.stride(3), s[4] * s[5] * s[6]);
        EXPECT_EQ(a.stride(4), s[5] * s[6]);
        EXPECT_EQ(a.stride(5), s[6]);
        EXPECT_EQ(a.stride(6), 1);

        const auto str = a.strides();
        EXPECT_EQ(str.size(), 7U);
        EXPECT_EQ(str[0], s[1] * s[2] * s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(str[1], s[2] * s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(str[2], s[3] * s[4] * s[5] * s[6]);
        EXPECT_EQ(str[3], s[4] * s[5] * s[6]);
        EXPECT_EQ(str[4], s[5] * s[6]);
        EXPECT_EQ(str[5], s[6]);
        EXPECT_EQ(str[6], 1);
    }
    {
        const nd::vector<bool> a(10);
        EXPECT_EQ(a.stride(0), 1);

        const auto str = a.strides();
        EXPECT_EQ(str.size(), 1U);
        EXPECT_EQ(str[0], 1);
    }
    {
        const nd::vector<bool> a(1, 1, 1);
        EXPECT_EQ(a.stride(0), 1);
        EXPECT_EQ(a.stride(1), 1);
        EXPECT_EQ(a.stride(2), 1);

        const auto str = a.strides();
        EXPECT_EQ(str.size(), 3U);
        EXPECT_EQ(str[0], 1);
        EXPECT_EQ(str[1], 1);
        EXPECT_EQ(str[2], 1);
    }
}
