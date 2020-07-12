# MIT License
#
# Copyright (c) 2018-2020 Benjamin Köhler
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.10)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)

project(ndcontainer
        VERSION ${MAJOR_VERSION}.${MINOR_VERSION}
        LANGUAGES CXX)

set(LIB_NAME ndcontainer)
set(NAMESPACE bk::)

include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

# ------------------------------------------------------------------------------------------------------------------------------------
# options
# ----------
#option(BUILD_TESTS "Build test executables" OFF)
#option(BUILD_EXAMPLES "Build example executables" OFF)
option(BUILD_TESTS "Build test executables" On)
option(BUILD_EXAMPLES "Build example executables" On)

set(ND_DEFAULT_BUILD_TYPE "Release")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${ND_DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${ND_DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# PRINT

message(STATUS "---------------------------")
message(STATUS "nd::container options:")
message(STATUS "-      BUILD_TESTS: ${BUILD_TESTS}")
message(STATUS "-   BUILD_EXAMPLES: ${BUILD_EXAMPLES}")
message(STATUS "- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# ------------------------------------------------------------------------------------------------------------------------------------
# header-only library
# ----------
add_library(${LIB_NAME} INTERFACE)
add_library(${NAMESPACE}${LIB_NAME} ALIAS ${LIB_NAME})

target_compile_features(${LIB_NAME} INTERFACE cxx_std_17)
target_compile_definitions(${LIB_NAME} INTERFACE LIBRARY_HEADER_ONLY)

set_target_properties(${LIB_NAME} PROPERTIES
        INTERFACE_VERSION ${PROJECT_VERSION}
        INTERFACE_SOVERSION ${PROJECT_VERSION})

get_target_property(nd_version ${LIB_NAME} INTERFACE_VERSION)
message(STATUS "-          VERSION: ${nd_version}")
message(STATUS "---------------------------")

target_include_directories(${LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# INSTALL

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nd
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h")

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt
        DESTINATION ${CMAKE_INSTALL_DOCDIR})

install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT ${LIB_NAME}Targets
        FILE ${LIB_NAME}Targets.cmake
        NAMESPACE ${NAMESPACE}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME})

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${LIB_NAME}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME})

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME})

export(EXPORT ${LIB_NAME}Targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/${LIB_NAME}Targets.cmake
        NAMESPACE ${NAMESPACE})

# ------------------------------------------------------------------------------------------------------------------------------------
# dependencies (third party)
# ----------
if (BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/thirdparty/googletest EXCLUDE_FROM_ALL)
    mark_as_advanced(FORCE VAR BUILD_GMOCK)
    mark_as_advanced(FORCE VAR INSTALL_GTEST)

    enable_testing()
endif ()

# ------------------------------------------------------------------------------------------------------------------------------------
# helpers
# ----------
if (BUILD_TESTS OR BUILD_EXAMPLES)
    function(ConfigureTest name)
        target_include_directories(${name} PRIVATE $<BUILD_INTERFACE:${gtest_SOURCE_DIR}/include>)
        target_include_directories(${name} PRIVATE $<BUILD_INTERFACE:${gtest_SOURCE_DIR}>)
        target_link_libraries(${name} PRIVATE gtest_main)

        target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
        target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests")

        target_compile_features(${name} PRIVATE cxx_std_17)

        string(TOLOWER ${CMAKE_BUILD_TYPE} build_type_lowercase)
        if (build_type_lowercase STREQUAL "debug")
            target_compile_definitions(${name} PRIVATE ND_DEBUG)
        endif ()

        if (UNIX)
            target_compile_options(${name} PRIVATE
                    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
                    -pipe -march=native
                    $<$<CONFIG:Release>:-O3 -Wall -Wextra -Wpedantic -flto>
                    $<$<CONFIG:Debug>:-O0 -Wall -Wextra -Wpedantic -g -ggdb>>
                    $<$<CXX_COMPILER_ID:MSVC>:
                    $<$<CONFIG:Debug>:/Od /Wall /Zi>>)
        else ()
            target_compile_options(${name} PRIVATE
                    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
                    -pipe -march=native
                    $<$<CONFIG:Release>: -O3 -Wall -Wextra -Wpedantic>
                    $<$<CONFIG:Debug>:-O0 -Wall -Wextra -Wpedantic -g -ggdb>>
                    $<$<CXX_COMPILER_ID:MSVC>:
                    $<$<CONFIG:Debug>:/Od /Wall /Zi>>)
        endif ()
    endfunction()

    if (WIN32)
        set(BINARY_SUFFIX ".exe")
    else ()
        set(BINARY_SUFFIX "")
    endif ()
endif ()


# ------------------------------------------------------------------------------------------------------------------------------------
# examples
# ----------
if (BUILD_EXAMPLES)
    add_executable(example examples/example.cpp)
    ConfigureTest(example)

    install(FILES "$<TARGET_FILE_DIR:example>/example${BINARY_SUFFIX}"
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
            DESTINATION ${INSTALL_DIR}${CMAKE_INSTALL_BINDIR})
endif ()

if (BUILD_TESTS)
    add_executable(run_tests
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
            #
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_ctor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_assignment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_fill.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_set_values.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_cast.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_num_dimensions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_size.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_empty.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_swap.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_swap_external.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_stride.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_is_valid_ids.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_list_to_grid_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_grid_to_list_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_data.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_single_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_multi_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_front.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_back.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_operators_compare.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_iterator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_factory_constant.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_factory_one.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_factory_zero.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_to_string.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_operator_stream.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_at.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_iterator_arithmetic_operators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_iterator_comparison.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/array/test_array_reverse_iterator_arithmetic_operators.cpp
            #
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_assignment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_at.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_clear.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_ctor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_back.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_cast.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_data.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_empty.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_fill.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_front.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_grid_to_list_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_is_valid_ids.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_iterator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_iterator_arithmetic_operators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_iterator_comparison.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_multi_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_list_to_grid_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_num_dimensions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_operator_assignment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_operator_stream.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_operators_compare.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_reverse_iterator_arithmetic_operators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_set_values.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_single_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_size.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_stride.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_swap.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_swap_external.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector/test_vector_to_string.cpp#
            #
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_assignment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_at.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_clear.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_ctor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_back.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_cast.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_data.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_empty.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_fill.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_front.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_grid_to_list_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_is_valid_ids.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_iterator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_iterator_arithmetic_operators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_iterator_comparison.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_multi_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_list_to_grid_id.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_num_dimensions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_operator_assignment.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_operator_stream.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_operators_compare.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_reverse_iterator_arithmetic_operators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_set_values.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_single_index_operator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_size.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_stride.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_swap.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_swap_external.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grid/test_grid_to_string.cpp
            )

    ConfigureTest(run_tests)
    add_test(NAME run_tests COMMAND run_tests${BINARY_SUFFIX})

    install(FILES "$<TARGET_FILE_DIR:run_tests>/run_tests${BINARY_SUFFIX}"
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
            DESTINATION ${INSTALL_DIR}${CMAKE_INSTALL_BINDIR})
endif ()