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

TEST(nd_array, data)
{
    {
        nd::array<std::uint16_t, 5> a;
        auto&& d = a.data();

        const bool islref = std::is_lvalue_reference_v<decltype(d)>;
        EXPECT_TRUE(islref);

        const bool isconst = std::is_const_v<decltype(d)>;
        EXPECT_FALSE(isconst);

        const bool isrref = std::is_rvalue_reference_v<decltype(d)>;
        EXPECT_FALSE(isrref);
    }
    {
        const nd::array<std::uint16_t, 5> a;
        auto&& d = a.data();

        const bool islref = std::is_lvalue_reference_v<decltype(d)>;
        EXPECT_TRUE(islref);

        //const bool isconst = std::is_const_v<decltype(d)>;
        //EXPECT_TRUE(isconst);

        const bool isrref = std::is_rvalue_reference_v<decltype(d)>;
        EXPECT_FALSE(isrref);
    }
    {
        nd::array<std::uint16_t, 5> a;
        auto&& d = std::move(a).data();

        const bool islref = std::is_lvalue_reference_v<decltype(d)>;
        EXPECT_FALSE(islref);

        const bool isconst = std::is_const_v<decltype(d)>;
        EXPECT_FALSE(isconst);

        const bool isrref = std::is_rvalue_reference_v<decltype(d)>;
        EXPECT_TRUE(isrref);
    }
}
