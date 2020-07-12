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

TEST(nd_vector, clear)
{
    nd::vector<int> a;
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.data().capacity(), 0U);

    a.reserve(10, 10);
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.data().capacity(), 100U);

    a.resize({3, 10}, 5);
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.num_values(), 30U);
    EXPECT_EQ(a.data().capacity(), 30U);
    EXPECT_TRUE(std::all_of(a.begin(), a.end(), [](int x){return x == 5;}));

    a.resize(3, 10);
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.num_values(), 30U);
    EXPECT_EQ(a.data().capacity(), 30U);

    a.clear();
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.data().capacity(), 30U);

    a.shrink_to_fit();
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.data().capacity(), 0U);
}