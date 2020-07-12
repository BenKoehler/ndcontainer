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

#include <array>
#include <iostream>

#include <nd/array.h>
#include <nd/vector.h>
#include <nd/grid.h>

void
ndarray_example()
{
    {
        nd::grid<int, 2> a;
        a.resize({3, 4}, 0);

        int cnt = 0;
        for (std::size_t x = 0; x < a.size(0); ++x)
        {
            for (std::size_t y = 0; y < a.size(1); ++y)
            {
                a(x, y) = cnt++;
            }
        }

        std::cout << a << std::endl;

        std::iota(a.begin(), a.end(), 0);
        std::cout << a << std::endl;
    }

    std::cout << "NDArray example:" << std::endl;
    std::cout << "----------------" << std::endl;

    /*
     * - compile-time version (constexpr)
     * - example: 2 x 4 grid
     */
    constexpr nd::array<int, 2, 4> a(1, 2, 3, 4, 5, 6, 7, 8); // column-wise storage

    std::cout << a.num_values() << std::endl << std::endl;
    // output: 8

    std::cout << "size of dim 1: " << a.size(1) << std::endl << std::endl;
    // output: size of dim 1: 4

    [[maybe_unused]] constexpr auto size = a.size(); // std::array<unsigned int, 2>

    std::cout << a << std::endl << std::endl;
    // output: [[1, 5]
    //          [2, 6]
    //          [3, 7]
    //          [4, 8]]

    for (auto x: a)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // output: 1 2 3 4 5 6 7 8

    std::cout << a.empty() << std::endl;
    // output: 0

    std::cout << a(1, 1) << std::endl;
    // output: 6

    /*
     * - runtime version
     * - example: 2 x 2 x 3 x 1 grid
     */
    nd::array<double, 2, 2, 3, 1> b;

    b.fill(1337.0);
    std::cout << b << std::endl << std::endl;
    // output: [(0,0,0,0):1337, (0,0,1,0):1337, (0,0,2,0):1337, (0,1,0,0):1337, (0,1,1,0):1337, (0,1,2,0):1337, (1,0,0,0):1337, (1,0,1,0):1337, (1,0,2,0):1337, (1,1,0,0):1337, (1,1,1,0):1337, (1,1,2,0):1337]

    b.set_values(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);
    std::cout << b << std::endl << std::endl;
    // output: [(0,0,0,0):1, (0,0,1,0):2, (0,0,2,0):3, (0,1,0,0):4, (0,1,1,0):5, (0,1,2,0):6, (1,0,0,0):7, (1,0,1,0):8, (1,0,2,0):9, (1,1,0,0):10, (1,1,1,0):11, (1,1,2,0):12]

    b(1, 1, 1, 0) = 9999;
    std::cout << b << std::endl << std::endl;
    // output: [(0,0,0,0):1, (0,0,1,0):2, (0,0,2,0):3, (0,1,0,0):4, (0,1,1,0):5, (0,1,2,0):6, (1,0,0,0):7, (1,0,1,0):8, (1,0,2,0):9, (1,1,0,0):10, (1,1,1,0):9999, (1,1,2,0):12]

    std::cout << (a == b) << std::endl;
    // output: 0

    // b(5,5,5,5); // // crash; assertion fails because of invalid ids
    // b.at(5,5,5,5); // throws std::out_of_range
    // b(0,0,0) = 6; // static_assert fails "invalid number of arguments"
    // b(std::array<int,3>{0,0,0}) = 6; // crash; assertion fails because of invalid number of arguments
}

void
ndvector_example()
{
    std::cout << "NDVector example:" << std::endl;
    std::cout << "-----------------" << std::endl;

    nd::vector<float> v;
    v.resize(6); // 1D vector of size 6
    std::iota(v.begin(), v.end(), 3);
    std::cout << v << std::endl << std::endl;
    // output: [3, 4, 5, 6, 7, 8]

    v.resize(2, 3); // reshape to 2D vector of size 2x3
    std::cout << v << std::endl << std::endl;
    // output: [[3, 6]
    //          [4, 7]
    //          [5, 8]]

    v.clear();
    v.reserve(3);
    v.resize(3);
    for (int i : {0, 1, 2})
    {
        v(i) = 2 * i;
    }
    std::cout << v << std::endl << std::endl;
    // output: [0, 2, 4]

    v.resize(1, 3); // resize v to a 2D vector of size 1x3 (a column)
    std::cout << v << std::endl;
    // output: [[0]
    //          [2]
    //          [4]]

    v.resize(2, 3); // resize v to a 2D vector of size 2x3 (a column)
    std::cout << v << std::endl;
    // output: [[0, 0]
    //          [2, 0]
    //          [4, 0]]

    v(1, 0) = 7;
    v(1, 1) = 8;
    v(1, 2) = 9;
    std::cout << v << std::endl << std::endl;
    // output: [[0, 7]
    //          [2, 8]
    //          [4, 9]]

    v.resize(2, 2, 2); // resize v to a 2x2x2 vector, which can be interpreted as the corners of a cube
    v.fill(1);
    std::cout << v << std::endl << std::endl;
    // output: [(0,0,0)=1, (0,0,1)=1, (0,1,0)=1, (0,1,1)=1, (1,0,0)=1, (1,0,1)=1, (1,1,0)=1, (1,1,1)=1]

    v.resize(2, 2, 3);
    v(0, 0, 2) = 13;
    v(0, 1, 2) = 14;
    v(1, 1, 2) = 15;
    v(1, 0, 2) = 16;
    std::cout << v << std::endl << std::endl;
    // output: [(0,0,0)=1, (0,0,1)=1, (0,0,2)=13, (0,1,0)=1, (0,1,1)=1, (0,1,2)=14, (1,0,0)=1, (1,0,1)=1, (1,0,2)=16, (1,1,0)=0, (1,1,1)=0, (1,1,2)=15]

    v.clear();
    v.reserve(16);
    v.resize(4, 4);
    v(3, 3) = 1;
    std::cout << v << std::endl << std::endl;
    // output: [[0, 0, 0, 0]
    //          [0, 0, 0, 0]
    //          [0, 0, 0, 0]
    //          [0, 0, 0, 1]]

    v.clear();
    v.reserve(25);
    v.resize(5, 5);
    for (int x: {0, 1, 2, 3, 4})
    {
        for (int y: {0, 1, 2, 3, 4})
        {
            v(x, y) = x * y;
        }
    }
    std::cout << v << std::endl;
    // output: [[0, 0, 0, 0, 0]
    //          [0, 1, 2, 3, 4]
    //          [0, 2, 4, 6, 8]
    //          [0, 3, 6, 9, 12]
    //          [0, 4, 8, 12, 16]]

    //NDVector<int> w(2);
    //std::cout << w(Vec2i(0,3)) << std::endl;
    //std::cout << w << std::endl;

    // here, new memory cannot be allocated because w is const
    const nd::vector<int> w(2, 3);
    //std::cout << w(std::array<int,2>{0,3}) << std::endl; // crash; assertion fails because of invalid ids
    //std::cout << w.at(std::array<int,2>{0,3}) << std::endl; // throws std::out_of_range

    std::cout << std::endl;

    std::array<unsigned int, 3> size2{3, 4, 5};
    std::cout << "custom size via std::array<int,3>: " << size2[0] << " " << size2[1] << " " << size2[2] << std::endl;
    nd::vector<double> c(size2.begin(), size2.end());
    std::cout << "nd::vector size via std::array<int,3>: " << c.size(0) << " " << c.size(1) << " " << c.size(2) << std::endl;
    std::cout << "\tnum values: " << c.num_values() << std::endl; // 60
}

void
ndgrid_example()
{
    {
        // 2d vector field (f(x,y) -> [u,v])
        nd::grid<std::array<double, 2>, 2> f;
        f.reserve(16);
        f.resize(4, 3);

        for (std::size_t x = 0; x < f.size(0); ++x)
        {
            for (std::size_t y = 0; y < f.size(1); ++y)
            {
                f(x, y) = {static_cast<double>(x), static_cast<double>(y)};
            }
        }

        for (std::size_t x = 0; x < f.size(0); ++x)
        {
            for (std::size_t y = 0; y < f.size(1); ++y)
            {
                std::cout << "f(" << x << ", " << y << ") -> [ ";
                for (std::size_t u = 0; u < 2; ++u)
                {
                    std::cout << f(x, y)[u] << " ";
                }
                std::cout << "]" << std::endl;
            }
        }
        std::cout << std::endl;
        // output: f(0, 0) -> [ 0 0 ]
        //         f(0, 1) -> [ 0 1 ]
        //         f(0, 2) -> [ 0 2 ]
        //         f(1, 0) -> [ 1 0 ]
        //         f(1, 1) -> [ 1 1 ]
        //         f(1, 2) -> [ 1 2 ]
        //         f(2, 0) -> [ 2 0 ]
        //         f(2, 1) -> [ 2 1 ]
        //         f(2, 2) -> [ 2 2 ]
        //         f(3, 0) -> [ 3 0 ]
        //         f(3, 1) -> [ 3 1 ]
        //         f(3, 2) -> [ 3 2 ]

        f.resize(3, 3);
        for (std::size_t x = 0; x < f.size(0); ++x)
        {
            for (std::size_t y = 0; y < f.size(1); ++y)
            {
                std::cout << "f(" << x << ", " << y << ") -> [ ";
                for (std::size_t u = 0; u < 2; ++u)
                {
                    std::cout << f(x, y)[u] << " ";
                }
                std::cout << "]" << std::endl;
            }
        }
        std::cout << std::endl;
        // output: f(0, 0) -> [ 0 0 ]
        //         f(0, 1) -> [ 0 1 ]
        //         f(0, 2) -> [ 0 2 ]
        //         f(1, 0) -> [ 1 0 ]
        //         f(1, 1) -> [ 1 1 ]
        //         f(1, 2) -> [ 1 2 ]
        //         f(2, 0) -> [ 2 0 ]
        //         f(2, 1) -> [ 2 1 ]
        //         f(2, 2) -> [ 2 2 ]
    }
    {
        // 2d vector field where vector is embedded in image dimensions
        nd::grid<int, 3> f({3, 3, 2}, 5);

        for (std::size_t x = 0; x < f.size(0); ++x)
        {
            for (std::size_t y = 0; y < f.size(1); ++y)
            {
                std::cout << "f(" << x << ", " << y << ") -> [ ";
                for (std::size_t u = 0; u < f.size(2); ++u)
                {
                    std::cout << f(x, y, u) << " ";
                }
                std::cout << "]" << std::endl;
            }
        }
        std::cout << std::endl;
        // output: f(0, 0) -> [ 5 5 ]
        //         f(0, 1) -> [ 5 5 ]
        //         f(0, 2) -> [ 5 5 ]
        //         f(1, 0) -> [ 5 5 ]
        //         f(1, 1) -> [ 5 5 ]
        //         f(1, 2) -> [ 5 5 ]
        //         f(2, 0) -> [ 5 5 ]
        //         f(2, 1) -> [ 5 5 ]
        //         f(2, 2) -> [ 5 5 ]
    }
}

int
main(int, char**)
{
    ndarray_example();
    std::cout << std::endl;

    ndvector_example();
    std::cout << std::endl;

    ndgrid_example();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
