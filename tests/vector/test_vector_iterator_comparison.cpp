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

TEST(nd_vector, iterator_comparison)
{
    {
        nd::vector<int> a(1, 1, 4);
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        a[3] = 4;

        const auto it0 = a.begin();
        const auto it1 = a.begin() + 1;

        const bool eq = it0 == it1;
        const bool neq = it0 != it1;
        const bool less = it0 < it1;
        const bool less_equal = it0 <= it1;
        const bool greater = it0 > it1;
        const bool greater_equal = it0 >= it1;

        EXPECT_FALSE(eq);
        EXPECT_TRUE(neq);
        EXPECT_TRUE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_FALSE(greater_equal);
    }
    {
        nd::vector<int> a(1, 1, 4);
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        a[3] = 4;

        const auto it0 = a.begin();
        const auto it1 = it0;

        const bool eq = it0 == it1;
        const bool neq = it0 != it1;
        const bool less = it0 < it1;
        const bool less_equal = it0 <= it1;
        const bool greater = it0 > it1;
        const bool greater_equal = it0 >= it1;

        EXPECT_TRUE(eq);
        EXPECT_FALSE(neq);
        EXPECT_FALSE(less);
        EXPECT_TRUE(less_equal);
        EXPECT_FALSE(greater);
        EXPECT_TRUE(greater_equal);
    }
}
