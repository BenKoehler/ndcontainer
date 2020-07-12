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

TEST(nd_vector, empty)
{
    {
        const bool b = nd::vector<int>(3, 2).empty();
        EXPECT_FALSE(b);
    }
    {
        const bool b = nd::vector<int>(1).empty();
        EXPECT_FALSE(b);
    }
    {
        const bool b = nd::vector<int>(1, 1, 1).empty();
        EXPECT_FALSE(b);
    }
    {
        const bool b = nd::vector<bool>(5, 6, 7, 8).empty();
        EXPECT_FALSE(b);
    }
    {
        nd::vector<std::string> x;
        EXPECT_TRUE(x.empty());
        x.reserve(4, 3);
        EXPECT_TRUE(x.empty());
        x.resize(4, 3);
        EXPECT_FALSE(x.empty());
    }
}
