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

TEST(nd_vector, data)
{
    {
        nd::vector<std::string> a(5);
        a[0] = "a";
        a[1] = "b";
        a[2] = "c";
        a[3] = "d";
        a[4] = "e";
        auto&& d = a.data();
        EXPECT_FALSE(a.empty());
        EXPECT_FALSE(d.empty());
    }
    {
        const nd::vector<double> a(3);
        auto&& d = a.data();
        EXPECT_FALSE(a.empty());
        EXPECT_FALSE(d.empty());
    }
    {
        nd::vector<std::size_t> a(10);
        EXPECT_EQ(a.num_dimensions(), 1U);
        EXPECT_EQ(a.size(0), 10U);
        EXPECT_EQ(a.num_values(), 10U);

        for (std::size_t i = 0; i < 10U; ++i)
        { a[i] = 2U * i; }

        std::vector<std::size_t> d = std::move(a).data();
        EXPECT_TRUE(a.empty());
        EXPECT_FALSE(d.empty());
    }
}
