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

TEST(nd_vector, ctor)
{
    {
        [[maybe_unused]] nd::vector<int> a(3, 2);
        EXPECT_EQ(a.num_dimensions(), 2U);
        EXPECT_EQ(a.size().size(), 2U);
        EXPECT_EQ(a.size()[0], 3U);
        EXPECT_EQ(a.size(0), 3U);
        EXPECT_EQ(a.size()[1], 2U);
        EXPECT_EQ(a.size(1), 2U);
        EXPECT_EQ(a.strides().size(), 2U);
        EXPECT_EQ(a.stride(0), 2U);
        EXPECT_EQ(a.strides()[0], 2U);
        EXPECT_EQ(a.stride(1), 1U);
        EXPECT_EQ(a.strides()[1], 1U);

        for (auto x : a.data())
        { EXPECT_EQ(x, 0); }
    }
    {
        [[maybe_unused]] nd::vector<int> a(2, 2, 1, 3);
        EXPECT_EQ(a.num_dimensions(), 4U);
        EXPECT_EQ(a.num_values(), 2U * 2U * 1U * 3U);
        EXPECT_EQ(a.size().size(), 4U);
        EXPECT_EQ(a.size()[0], 2U);
        EXPECT_EQ(a.size(0), 2U);
        EXPECT_EQ(a.size()[1], 2U);
        EXPECT_EQ(a.size(1), 2U);
        EXPECT_EQ(a.size()[2], 1U);
        EXPECT_EQ(a.size(2), 1U);
        EXPECT_EQ(a.size()[3], 3U);
        EXPECT_EQ(a.size(3), 3U);
        EXPECT_EQ(a.strides().size(), 4U);
        EXPECT_EQ(a.stride(0), 2U * 1U * 3U);
        EXPECT_EQ(a.stride(1), 1U * 3U);
        EXPECT_EQ(a.stride(2), 3U);
        EXPECT_EQ(a.stride(3), 1U);
        for (std::size_t i = 0; i < 4U; ++i)
        { EXPECT_EQ(a.strides()[i], a.stride(i)); }

        a[0] = 1337;
        EXPECT_EQ(a[0], 1337);

        [[maybe_unused]] nd::vector<int> b(a);
        EXPECT_EQ(b.num_dimensions(), a.num_dimensions());
        EXPECT_EQ(b.num_values(), a.num_values());
        EXPECT_EQ(b.size().size(), a.size().size());
        EXPECT_EQ(b.strides().size(), a.strides().size());
        for (std::size_t i = 0; i < b.num_dimensions(); ++i)
        {
            EXPECT_EQ(b.strides()[i], a.strides()[i]);
            EXPECT_EQ(b.size()[i], a.size()[i]);
        }

        auto itA = a.data().begin();
        auto itB = b.data().begin();
        for (; itA != a.data().end(); ++itA, ++itB)
        { EXPECT_EQ(*itA, *itB); }
    }
    {
        std::array<int, 2> s{5, 6};
        [[maybe_unused]] nd::vector<int> a(s.begin(), s.end());
        EXPECT_EQ(a.num_dimensions(), s.size());
        for (std::size_t i = 0; i < s.size(); ++i)
        { EXPECT_EQ(a.size(i), s[i]); }
    }
    {
        std::vector<int> s{5, 6, 7, 8};
        [[maybe_unused]] nd::vector<int> a(s.begin(), s.end());
        EXPECT_EQ(a.num_dimensions(), s.size());
        for (std::size_t i = 0; i < s.size(); ++i)
        { EXPECT_EQ(a.size(i), s[i]); }
    }
    {
        [[maybe_unused]] nd::vector<int> a({2, 1, 3});
        EXPECT_EQ(a.num_dimensions(), 3U);
        EXPECT_EQ(a.size(0), 2U);
        EXPECT_EQ(a.size(1), 1U);
        EXPECT_EQ(a.size(2), 3U);
    }
    {
        nd::vector<int> a(50);
        a[0] = 5;
        EXPECT_EQ(a.num_dimensions(), 1U);
        EXPECT_EQ(a.size(0), 50U);
        EXPECT_EQ(a[0], 5);

        const nd::vector<int> b(std::move(a));
        EXPECT_TRUE(a.empty());
        EXPECT_EQ(b.num_dimensions(), 1U);
        EXPECT_EQ(b.num_values(), 50U);
        EXPECT_EQ(b[0], 5);
    }
    { // use initializer list and default value
        const nd::vector<short> a({1, 2, 3, 4, 5}, static_cast<short>(1337));
        EXPECT_EQ(a.num_dimensions(), 5U);
        EXPECT_EQ(a.size(0), 1U);
        EXPECT_EQ(a.size(1), 2U);
        EXPECT_EQ(a.size(2), 3U);
        EXPECT_EQ(a.size(3), 4U);
        EXPECT_EQ(a.size(4), 5U);
        EXPECT_EQ(a.num_values(), 1U * 2U * 3U * 4U * 5U);
        for (auto x : a)
        { EXPECT_EQ(x, static_cast<short>(1337)); }
    }
    { // use initializer list and default value
        const nd::vector<std::string> a({20}, "foo");
        EXPECT_EQ(a.num_dimensions(), 1U);
        EXPECT_EQ(a.size(0), 20U);
        EXPECT_EQ(a.num_values(), 20U);
        for (auto x : a)
        { EXPECT_EQ(x, "foo"); }
    }
}
