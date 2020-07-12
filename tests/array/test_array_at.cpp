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

TEST(nd_array, at)
{
    {
        constexpr nd::array<int, 3> a(4, 6, 8);

        constexpr auto x0 = a.at_grid<0>();
        EXPECT_EQ(x0, a[0]);

        constexpr auto x1 = a.at_grid<1>();
        EXPECT_EQ(x1, a[1]);

        constexpr auto x2 = a.at_grid<2>();
        EXPECT_EQ(x2, a[2]);

        //constexpr auto x3 = a.at_grid<3>(); // expect does not compile
    }
    {
        constexpr nd::array<int, 3, 1, 2> a(1, 2, 3, 4, 5, 6);
        constexpr auto x0 = a.at_grid<0, 0, 0>();
        EXPECT_EQ(x0, a[0]);

        constexpr auto x1 = a.at_grid<0, 0, 1>();
        EXPECT_EQ(x1, a[1]);

        constexpr auto x2 = a.at_grid<2, 0, 1>();
        EXPECT_EQ(x2, a.back());

        //constexpr auto x3 = a.at_grid<0,1,0>(); // expect does not compile
        //constexpr auto x4 = a.at_grid<0,0>(); // expect does not compile
    }
}
