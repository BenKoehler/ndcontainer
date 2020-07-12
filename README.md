### OVERVIEW

ndcontainer provides generic, N-dimensional data containers where 
either all sizes are known at compile-time, 
the number of dimensions is known at compile-time or 
everything is known at run-time only:

| *Dimensions*   | *Sizes*        |    | *ndcontainer*            | *Example* |
|:--------------:|:--------------:|----|--------------------------|:---------:|
| compile-time   | compile-time   | => | nd::array< T, Sizes... > | 3x3 Binomial kernel used for image smoothing via convolution  |
| compile-time   | run-time       | => | nd::grid< T, NumDims >   | Data storage for a matrix class (2D) or for a 2D image, e.g., from reading a PNG file |
| run-time       | run-time       | => | nd::vector< T >          | Read DICOM images where the number of dimension is derived from the DICOM tags |

##### Features 

- C++17
- Header-only
- constexpr support for nd::array
- easy integration into your project
- comes with a bunch of sanity tests using GoogleTest

##### Functions

| *Function*   | Description  
|:--------------------------|---|
| size | Get sizes per dimension in a container or the size of a particular dimension |
| resize | Set the grid size via individual indices, e.g. (4,3), via an initializer_list / iterators and a default value, e.g. ({4,3}, 0) or (s.begin(), s.end(), 0) | 
| empty | Does the container hold any values? | 
| operator()<br>at_grid | Access value at grid position. at_grid() throws when out of bounds. A Grid position can be provided as individual coordinates, e.g. (2,0,1), an index-accessible container, e.g. std::array<int,3>{2,0,1}, or a plain array/pointer, e.g. int pos[3] = {2,0,1} |
| operator[]<br>at_list | Access value via internal, linear data storage. at_list() throws when out of bounds. grid_to_list_id() or stride() functions may be helpful |
| front<br>back | Access first / last value of internal data storage | 
| begin<br>end<br>rbegin<br>rend | (Reverse) Iterators for internal data storage | 
| stride | Get strides per dimension in a container or the stride of a particular dimension. Can be used for data access via list index | 
| list_to_grid_id<br>grid_to_list_id | Convert a list index (as used in internal data storage) to a container with grid positions or the other way around. Grid position can be individual coordinates, e.g. (2,0,1), a index-accessible container, e.g. std::array<int,3>{2,0,1}, or a plain array/pointer, e.g. int pos[3] = {2,0,1} | 
| data | Access internal, linear data storage | | 
| operator==<br>operator!=<br>operator<=<br>operator<<br>operator>=<br>operator> | compare containers by sizes and values | 
| swap | swap contents. Provided as member functions as well as free functions |
| clear | resize to 0 | 
| to_string<br>operator<< | create a string showing the values in a list (1D) / grid (2D) or as pair of coordinates of values (3D+). Stream operator uses to_string() | 
| cast | convert container to different value type | 
| fill | set each entry to the same value | 
|  | | 
|  | | 
|  | | 
 
##### Example: Initialize a 3x4 int container with constant value 5

```c++
constexpr nd::array<int, 3, 4> a = nd::array<int, 3, 4>::Constant(5); // use factory function

nd::grid<int, 2> b({3, 4}, 5); // use constructor

nd::vector<int> c({3, 4}, 5); // use constructor
```

##### Example: Resize and set values

```c++
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

// same as std::iota(a.begin(), a.end(), 0);
```

##### Example: examples/example.cpp

### INSTALLATION

##### Version 1: CMake add_subdirectory

Clone sources into your project:

```shell script
cd thirdparty
git clone https://github.com/BenKoehler/ndcontainer
```

Add in CMake:

```cmake
add_subdirectory(thirdparty/ndcontainer)

# create executable or library

target_link_libraries(myBinary PRIVATE bk::ndcontainer)
```

##### Version 2: Install using CMake

Clone sources:

```shell script
git clone https://github.com/BenKoehler/ndcontainer
```

Install using CMake:

```shell script
mkdir build
mkdir ndcontainer_install
cd build
cmake -DCMAKE_INSTALL_PREFIX=../ndcontainer_install ../ndcontainer/ .
make
make install
```

If you want to compile tests and examples, use:

```shell script
[...]
cmake -DCMAKE_INSTALL_PREFIX=../ndcontainer_install -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=On -DBUILD_EXAMPLES=On ../ndcontainer/ .
make -j 8
[...]
```

Add in CMake:
```cmake
set(ndcontainer_DIR "/ndcontainer_install/lib/cmake/ndcontainer/")
find_package(ndcontainer REQUIRED)

# create executable or library

target_link_libraries(myBinary PRIVATE bk::ndcontainer)
```

##### Version 3: Copy paste

The easiest way to include ndcontainer is to copy-paste the nd/ directory (or individual files) to your project.

Each container is header-only and self-contained.

### DETAILS 

- Data are stored internally in a 1D std::vector or std::array. For instance 3 dimensions xyz are stored like this:
```c++
listIndex = 0

for x : size x
    for y : size y
        for z : size z
            values[listIndex++]
```

- Strides are used internally to convert a grid position to a list index.
```c++
stride 0 = size 1 * size 2 * size 3 * ...
stride 1 =          size 2 * size 3 * ...
stride 2 =                   size 3 * ...
...
stride n-1 = 1
```

- If possible, sanity checks (static_assert) are performed at compile-time. For example:
```c++
constexpr nd::array<int,1,2> a;
a(0,0,0) = 0; // static_assert fails: invalid number of arguments

nd::grid<int,2> b;
b(0,0,0) = 0; // static_assert fails: invalid number of arguments

nd::vector<int> b(2);
b(0,0,0) = 0; // run-time assert fails: invalid number of arguments
```

- There are multiple options for vector-valued data:
```c++
nd::grid<std::array<double, 3>, 3> // Use a value type that represents a vector
    
nd::grid<double, 6> // Append the variable dimensions to the image dimensions
```
