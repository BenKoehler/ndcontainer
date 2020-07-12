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
#include "nd/grid.h"

TEST(nd_grid, cast)
{
    {
        const nd::grid<int, 2> a({5, 4}, 1);

        [[maybe_unused]] auto b = a.cast<double>();
        static_assert(std::is_same_v<decltype(b)::value_type, double>);

        for (std::size_t i = 0; i < a.num_dimensions(); ++i)
        {
            EXPECT_EQ(a.size(i), b.size(i));
        }

        for (std::size_t i = 0; i < a.num_values(); ++i)
        {
            EXPECT_EQ(a[i], b[i]);
        }
    }
    {
        struct Bar
        { /* empty class */ };

        struct Foo
        {
            [[nodiscard]] operator Bar() const
            {
                return Bar();
            }
        };

        const nd::grid<Foo, 2> a({1, 2});

        [[maybe_unused]] auto b = a.cast<Bar>();
        static_assert(std::is_same_v<decltype(b)::value_type, Bar>);

        for (std::size_t i = 0; i < a.num_dimensions(); ++i)
        {
            EXPECT_EQ(a.size(i), b.size(i));
        }
    }
}
