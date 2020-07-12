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

TEST(nd_vector, iterator_arithmetic_operators)
{
    nd::vector<int> a(2, 3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    a[5] = 6;
    auto it = a.begin();

    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*(it + 1), 2);
    EXPECT_EQ(*(it + 2), 3);
    it += 3;
    EXPECT_EQ(*it, 4);
    EXPECT_EQ(*(it + 1), 5);
    EXPECT_EQ(*(it + 2), 6);
    it = 3 + it;
    EXPECT_EQ(it, a.end());
    ++it;
    it += 1;
    it -= 2;
    --it;
    EXPECT_EQ(*it, 6);

    *it = 1;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(a[5], 1);

    EXPECT_EQ(std::distance(a.begin(), a.end()), 6);
}
