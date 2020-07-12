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

TEST(nd_vector, to_string)
{
    {
        nd::vector<int> a(5);
        a.set_values(1, 2, 3, 4, 5);
        [[maybe_unused]] const std::string str = a.to_string();
        EXPECT_FALSE(str.empty());
        //std::cout << "nd::vector<int, 5>(1, 2, 3, 4, 5):\n" << str << std::endl;
    }
    {
        nd::vector<int> a(2, 2);
        a.set_values(1, 2, 3, 4);
        [[maybe_unused]] const std::string str = a.to_string();
        EXPECT_FALSE(str.empty());
        //std::cout << "nd::vector<int, 2, 2>(1, 2, 3, 4):\n" << str << std::endl;
    }
    {
        nd::vector<int> a(2, 2, 2);
        a.set_values(1, 2, 3, 4, 5, 6, 7, 8);
        [[maybe_unused]] const std::string str = a.to_string();
        EXPECT_FALSE(str.empty());
        //std::cout << "nd::vector<int, 2, 2, 2>(1, 2, 3, 4, 5, 6, 7, 8):\n" << str << std::endl;
    }
}
