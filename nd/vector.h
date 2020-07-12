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

#pragma once

#ifndef __ND_VECTOR_H__8945u23895cuifnui34nf892348923m98r
#define __ND_VECTOR_H__8945u23895cuifnui34nf892348923m98r

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#if !defined(__GNUC__) || defined(__MINGW32__)
  #define ND_FORCE_INLINE __forceinline
#else // IF __GNUC__
  #define ND_FORCE_INLINE __attribute__((always_inline))
#endif // __GNUC__

namespace nd
{
template<typename TValue>
class vector
{
    //------------------------------------------------------------------------------------------------------
    // definitions
    //------------------------------------------------------------------------------------------------------
  public:
    using self_type = vector<TValue>;
    using value_type = TValue;
    using data_container_type = std::vector<value_type>;
    using size_type = unsigned int;
    using difference_type = int;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = typename data_container_type::iterator;
    using const_iterator = typename data_container_type::const_iterator;
    using reverse_iterator = typename data_container_type::reverse_iterator;
    using const_reverse_iterator = typename data_container_type::const_reverse_iterator;

    //------------------------------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------------------------------
  private:
    std::vector<size_type> _sizes;
    std::vector<size_type> _strides;
    data_container_type    _values;

    //------------------------------------------------------------------------------------------------------
    // class
    //------------------------------------------------------------------------------------------------------
  public:
    ND_FORCE_INLINE vector() = default;

    ND_FORCE_INLINE vector(const self_type&) = default;

    ND_FORCE_INLINE vector(self_type&&) noexcept = default;

    template<typename K, std::enable_if_t<!std::is_same_v<K, value_type>>* = nullptr>
    ND_FORCE_INLINE
    vector(const vector<K>& other) :
        _sizes(other.size())
        , _strides(other.strides())
        , _values(other.data().begin(), other.data().end())
    {
        static_assert(std::is_convertible_v<K, value_type>, "cannot cast types");
    }

    template<typename... TSizes, std::enable_if_t<std::conjunction_v<std::is_arithmetic<std::decay_t<TSizes>>...> && std::is_arithmetic_v<value_type>>* = nullptr>
    ND_FORCE_INLINE
    vector(TSizes... sizes) :
        vector({sizes...}, static_cast<value_type>(0))
    {
        static_assert(sizeof...(TSizes) != 0, "size arguments are missing");
        static_assert(std::conjunction_v<std::is_integral<TSizes>...>, "size arguments must be integral types");
    }

    template<typename... TSizes, std::enable_if_t<std::conjunction_v<std::is_arithmetic<std::decay_t<TSizes>>...> && !std::is_arithmetic_v<value_type>>* = nullptr>
    ND_FORCE_INLINE
    vector(TSizes... sizes) :
        vector({sizes...}, value_type())
    {
        static_assert(sizeof...(TSizes) != 0, "size arguments are missing");
        static_assert(std::conjunction_v<std::is_integral<TSizes>...>, "size arguments must be integral types");
    }

    template<typename TIndex>
    ND_FORCE_INLINE
    vector(std::initializer_list<TIndex> sizes, const value_type& defaultInitValue = value_type()) :
        _sizes(sizes.begin(), sizes.end())
        , _strides(_sizes.size(), 1U)
        , _values(num_values_from_sizes(), defaultInitValue)
    {
        assert(num_values_from_sizes() != 0 && "all size arguments must be >= 1");
        _calc_strides();
    }

    template<typename TForwardIterator, std::enable_if_t<!std::is_arithmetic_v<TForwardIterator>>* = nullptr>
    vector(TForwardIterator sizesBegin, TForwardIterator sizesEnd, const value_type& defaultInitValue = value_type())
    {
        resize(sizesBegin, sizesEnd, defaultInitValue);
        _calc_strides();
    }

    ND_FORCE_INLINE ~vector() = default;

    [[maybe_unused]] ND_FORCE_INLINE self_type&
    operator=(const self_type&) = default;

    [[maybe_unused]] ND_FORCE_INLINE self_type&
    operator=(self_type&&) noexcept = default;

    template<typename K, std::enable_if_t<!std::is_same_v<K, value_type>>* = nullptr>
    [[maybe_unused]] ND_FORCE_INLINE self_type&
    operator=(const vector<K>& other)
    {
        static_assert(std::is_convertible_v<K, value_type>, "cannot cast types");

        _sizes   = other.size();
        _strides = other.strides();

        _values.resize(other.num_values());
        std::copy(other.data().begin(), other.data().end(), _values.begin());

        return *this;
    }

    //------------------------------------------------------------------------------------------------------
    // cast
    //------------------------------------------------------------------------------------------------------
    template<typename T>
    [[nodiscard]] ND_FORCE_INLINE vector<T>
    cast() const
    {
        static_assert(std::is_convertible_v<value_type, T>, "cannot cast types");
        return vector<T>(*this);
    }

    //------------------------------------------------------------------------------------------------------
    // stride
    //------------------------------------------------------------------------------------------------------
  private:
    void
    _calc_strides()
    {
        _strides.resize(_sizes.size());

        for (size_type i = 0; i < num_dimensions(); ++i)
        {
            _strides[i] = 1U;

            for (size_type k = i + 1; k < num_dimensions(); ++k)
            {
                _strides[i] *= _sizes[k];
            }
        }

        _strides.shrink_to_fit();
    }

  public:

    [[nodiscard]] ND_FORCE_INLINE size_type
    stride(size_type dimId) const
    {
        return _strides[dimId];
    }

    [[nodiscard]] ND_FORCE_INLINE const std::vector<size_type>&
    strides() const
    {
        return _strides;
    }

    //------------------------------------------------------------------------------------------------------
    // sizes
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE size_type
    num_dimensions() const noexcept(noexcept(_sizes.size()))
    {
        return _sizes.size();
    }

    [[nodiscard]] ND_FORCE_INLINE const std::vector<size_type>&
    size() const
    {
        return _sizes;
    }

    [[nodiscard]] ND_FORCE_INLINE size_type
    size(size_type dimId) const
    {
        assert(dimId < num_dimensions() && "dimId exceeds num_dimensions()");
        return _sizes[dimId];
    }

    [[nodiscard]] ND_FORCE_INLINE bool
    empty() const
    {
        return _values.empty();
    }

    //------------------------------------------------------------------------------------------------------
    // list id / grid id conversion
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] std::vector<size_type>
    list_to_grid_id(size_type lid) const
    {
        assert(lid < num_values());

        std::vector<size_type> gid(num_dimensions());

        const auto str = strides();

        for (size_type i = 0; i < num_dimensions() - 1; ++i)
        {
            gid[i] = lid;

            for (size_type k = 0; k < i; ++k)
            {
                gid[i] -= str[k] * gid[k];
            }

            gid[i] /= str[i];
        }

        gid[num_dimensions() - 1] = lid;
        for (size_type i = 0; i < num_dimensions() - 1; ++i)
        {
            gid[num_dimensions() - 1] -= str[i] * gid[i];
        }

        return gid;
    }

  private:
    template<typename TIndexAccessible>
    [[nodiscard]] ND_FORCE_INLINE size_type
    _grid_to_list_id_index(TIndexAccessible&& gid) const
    {
        size_type lid = 0;

        for (size_type i = 0; i < num_dimensions(); ++i)
        {
            lid += stride(i) * gid[i];
        }

        return lid;
    }

    template<std::size_t I, typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE size_type
    _grid_to_list_id_pack(size_type gid0, Ids... gid) const
    {
        if constexpr (sizeof...(Ids) != 0)
        {
            return gid0 * stride(I) + _grid_to_list_id_pack<I + 1>(gid...);
        }
        else
        {
            return gid0 * stride(I);
        }
    }

  public:

    template<typename... Ids>
    [[nodiscard]] size_type
    grid_to_list_id(Ids&& ... ids) const
    {
        assert(is_valid_ids(ids...));

        constexpr bool isIndexPack           = std::conjunction_v<std::is_integral<std::remove_reference_t<Ids>>...>;
        constexpr bool isPlainArrayOrPointer = sizeof...(Ids) == 1 && (std::conjunction_v<std::is_array<std::remove_reference_t<Ids>>...> || std::conjunction_v<std::is_pointer<std::remove_reference_t<Ids>>...>);
        constexpr bool isClass               = sizeof...(Ids) == 1 && std::conjunction_v<std::is_class<std::remove_reference_t<Ids>>...>;

        static_assert(isIndexPack || isPlainArrayOrPointer || isClass, "Invalid number of arguments! "
                                                                       "Either provide N individual integral indices "
                                                                       "or provide a plain C-array / pointer / index[]-accessible class "
                                                                       "containing N indices! "
                                                                       "( N = num_dimensions() )");

        if constexpr (isIndexPack)
        {
            assert(sizeof...(Ids) == num_dimensions() && "invalid number of arguments");
            return _grid_to_list_id_pack<0>(std::forward<Ids>(ids)...);
        }
        else if constexpr (isPlainArrayOrPointer || isClass)
        {
            return _grid_to_list_id_index(std::forward<Ids>(ids)...);
        }

        return 0;
    }

    //------------------------------------------------------------------------------------------------------
    // data
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE data_container_type&
    data()& noexcept
    {
        return _values;
    }

    [[nodiscard]] ND_FORCE_INLINE const data_container_type&
    data() const& noexcept
    {
        return _values;
    }

    [[nodiscard]] ND_FORCE_INLINE data_container_type&&
    data()&& noexcept
    {
        return std::move(_values);
    }

    //------------------------------------------------------------------------------------------------------
    // num values
    //------------------------------------------------------------------------------------------------------
  private:
    [[nodiscard]] ND_FORCE_INLINE size_type
    num_values_from_sizes() const noexcept
    {
        return std::accumulate(_sizes.begin(), _sizes.end(), 1U, [](size_type x, size_type y)
        {
            return x * y;
        });
    }

  public:

    [[nodiscard]] ND_FORCE_INLINE size_type
    num_values() const noexcept(noexcept(_values.size()))
    {
        return _values.size();
    }

    //------------------------------------------------------------------------------------------------------
    // operator[]
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE reference
    operator[](size_type i)
    {
        assert(i < num_values() && "id out of bounds");
        return _values[i];
    }

    [[nodiscard]] ND_FORCE_INLINE const_reference
    operator[](size_type i) const
    {
        assert(i < num_values() && "id out of bounds");
        return _values[i];
    }

    //------------------------------------------------------------------------------------------------------
    // at list id
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE reference
    at_list(size_type id)
    {
        if (id >= num_values())
        {
            throw std::out_of_range("trying to access vector[" + std::to_string(id) + "] with size " + std::to_string(num_values()));
        }

        return _values[id];
    }

    [[nodiscard]] ND_FORCE_INLINE const_reference
    at_list(size_type id) const
    {
        if (id >= num_values())
        {
            throw std::out_of_range("trying to access vector[" + std::to_string(id) + "] with size " + std::to_string(num_values()));
        }

        return _values[id];
    }

    //------------------------------------------------------------------------------------------------------
    // helper: ids are valid
    //------------------------------------------------------------------------------------------------------
  private:
    template<int I = 0, typename Id, typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE bool
    _is_valid_index_pack(Id i0, Ids... in) const
    {
        if constexpr(sizeof...(Ids) != 0)
        {
            return i0 >= 0 && i0 < static_cast<Id>(_sizes[I]) && _is_valid_index_pack<I + 1>(in...);
        }
        else
        {
            return i0 >= 0 && i0 < static_cast<Id>(_sizes[I]);
        }
    }

    template<typename T>
    [[nodiscard]] ND_FORCE_INLINE bool
    _is_valid_index_accessible(T&& ids) const
    {
        using K = std::decay_t<decltype(ids[0])>;

        for (size_type i = 0; i < num_dimensions(); ++i)
        {
            if (ids[i] < static_cast<K>(0) || ids[i] >= static_cast<K>(_sizes[i]))
            {
                return false;
            }
        }

        return true;
    }

  public:

    template<typename... Ids>
    [[nodiscard]] bool
    is_valid_ids(Ids&& ... ids) const
    {
        constexpr bool isIndexPack           = std::conjunction_v<std::is_integral<std::remove_reference_t<Ids>>...>;
        constexpr bool isPlainArrayOrPointer = sizeof...(Ids) == 1 && (std::conjunction_v<std::is_array<std::remove_reference_t<Ids>>...> || std::conjunction_v<std::is_pointer<std::remove_reference_t<Ids>>...>);
        constexpr bool isClass               = sizeof...(Ids) == 1 && std::conjunction_v<std::is_class<std::remove_reference_t<Ids>>...>;

        static_assert(isIndexPack || isPlainArrayOrPointer || isClass, "Invalid number of arguments! "
                                                                       "Either provide N individual integral indices "
                                                                       "or provide a plain C-array / pointer / index[]-accessible class "
                                                                       "containing N indices! "
                                                                       "( N = num_dimensions() )");

        if constexpr (isIndexPack)
        {
            return sizeof...(Ids) == num_dimensions() && _is_valid_index_pack(std::forward<Ids>(ids)...);
        }
        else if constexpr (isPlainArrayOrPointer)
        {
            return _is_valid_index_accessible(std::forward<Ids>(ids)...);
        }
        else if constexpr (isClass)
        {
            if (std::get<0>(std::make_tuple(std::forward<Ids>(ids)...)).size() != num_dimensions())
            {
                return false;
            }

            return _is_valid_index_accessible(std::forward<Ids>(ids)...);
        }

        return false;
    }

  public:

    //------------------------------------------------------------------------------------------------------
    // operator()
    //------------------------------------------------------------------------------------------------------
    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE reference
    operator()(Ids&& ... ids)
    {
        assert(is_valid_ids(ids...));
        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE const_reference
    operator()(Ids&& ... ids) const
    {
        assert(is_valid_ids(ids...));
        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    //------------------------------------------------------------------------------------------------------
    // at grid
    //------------------------------------------------------------------------------------------------------
    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE reference
    at_grid(Ids&& ... ids)
    {
        if (!is_valid_ids(ids...))
        {
            throw std::out_of_range("invalid vector access!");
        }

        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE const_reference
    at_grid(Ids&& ... ids) const
    {
        if (!is_valid_ids(ids...))
        {
            throw std::out_of_range("invalid vector access!");
        }

        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    template<std::size_t... ids>
    [[nodiscard]] ND_FORCE_INLINE reference
    at_grid()
    {
        if (!is_valid_ids(ids...))
        {
            throw std::out_of_range("invalid vector access!");
        }

        return _values[grid_to_list_id(ids...)];
    }

    template<std::size_t... ids>
    [[nodiscard]] ND_FORCE_INLINE const_reference
    at_grid() const
    {
        if (!is_valid_ids(ids...))
        {
            throw std::out_of_range("invalid vector access!");
        }

        return _values[grid_to_list_id(ids...)];
    }

    //------------------------------------------------------------------------------------------------------
    // front / back
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE reference
    front() noexcept(noexcept(_values.front()))
    {
        return _values.front();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reference
    front() const noexcept(noexcept(_values.front()))
    {
        return _values.front();
    }

    [[nodiscard]] ND_FORCE_INLINE reference
    back() noexcept(noexcept(_values.back()))
    {
        return _values.back();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reference
    back() const noexcept(noexcept(_values.back()))
    {
        return _values.back();
    }

    //------------------------------------------------------------------------------------------------------
    // iterators
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE iterator
    begin() noexcept(noexcept(_values.begin()))
    {
        return _values.begin();
    }

    [[nodiscard]] ND_FORCE_INLINE const_iterator
    begin() const noexcept(noexcept(_values.begin()))
    {
        return _values.begin();
    }

    [[nodiscard]] ND_FORCE_INLINE iterator
    end() noexcept(noexcept(_values.end()))
    {
        return _values.end();
    }

    [[nodiscard]] ND_FORCE_INLINE const_iterator
    end() const noexcept(noexcept(_values.end()))
    {
        return _values.end();
    }

    [[nodiscard]] ND_FORCE_INLINE reverse_iterator
    rbegin() noexcept(noexcept(_values.rbegin()))
    {
        return _values.rbegin();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reverse_iterator
    rbegin() const noexcept(noexcept(_values.rbegin()))
    {
        return _values.rbegin();
    }

    [[nodiscard]] ND_FORCE_INLINE reverse_iterator
    rend() noexcept(noexcept(_values.rend()))
    {
        return _values.rend();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reverse_iterator
    rend() const noexcept(noexcept(_values.rend()))
    {
        return _values.rend();
    }

    //====================================================================================================
    //===== SETTER
    //====================================================================================================
    template<typename... TSizes, std::enable_if_t<std::conjunction_v<std::is_arithmetic<TSizes>...>>* = nullptr>
    void
    resize(TSizes... sizes)
    {
        static_assert(sizeof...(TSizes) != 0, "size arguments are missing");
        assert(((sizes > 0) && ...) && "all sizes must be > 0");

        _sizes = {static_cast<size_type>(sizes)...};
        _sizes.shrink_to_fit();

        _values.resize(num_values_from_sizes());
        _values.shrink_to_fit();

        _calc_strides();
    }

    template<typename T>
    void
    resize(std::initializer_list<T> sizes, const value_type& defaultValueInit)
    {
        assert(std::all_of(sizes.begin(), sizes.end(), [](T x){return x > 0;}) && "all sizes must be > 0");

        _sizes.resize(sizes.size());
        std::copy(sizes.begin(), sizes.end(), _sizes.begin());
        _sizes.shrink_to_fit();

        _values.resize(num_values_from_sizes(), defaultValueInit);
        _values.shrink_to_fit();

        _calc_strides();
    }

    template<typename TForwardIterator, std::enable_if_t<!std::is_arithmetic_v<std::decay_t<TForwardIterator>>>* = nullptr>
    void
    resize(TForwardIterator first, TForwardIterator last, const value_type& defaultValueInit = value_type())
    {
        _sizes.assign(first, last);
        _sizes.shrink_to_fit();
        assert(std::all_of(_sizes.begin(), _sizes.end(), [](size_type x)
        {
            return x > 0;
        }) && "all sizes must be > 0");

        _values.resize(num_values_from_sizes(), defaultValueInit);
        _values.shrink_to_fit();

        _calc_strides();
    }

    //------------------------------------------------------------------------------------------------------
    // clear
    //------------------------------------------------------------------------------------------------------
    void
    clear()
    {
        _values.clear();
        _sizes.clear();
        _strides.clear();
    }

    void
    shrink_to_fit()
    {
        _sizes.shrink_to_fit();
        _strides.shrink_to_fit();
        _values.shrink_to_fit();
    }

    //------------------------------------------------------------------------------------------------------
    // reserve
    //------------------------------------------------------------------------------------------------------
    template<typename TSize0, typename... TSizes>
    void
    reserve(TSize0 size0, TSizes... sizes)
    {
        static_assert(std::is_integral_v<std::decay_t<TSize0>> && std::conjunction_v<std::is_integral<TSizes>...>);
        assert(((sizes > 0) && ...) && "all sizes must be > 0");
        _values.reserve(size0 * (sizes * ... * 1U));
    }

    //------------------------------------------------------------------------------------------------------
    // set values
    //------------------------------------------------------------------------------------------------------
    template<typename... TValues>
    ND_FORCE_INLINE void
    set_values(TValues&& ... values)
    {
        assert(sizeof...(TValues) == num_values() && "invalid number of arguments");
        _values = {static_cast<value_type>(std::forward<TValues>(values))...};
    }

    void
    fill(const_reference value)
    {
        for (reference x: _values)
        {
            x = value;
        }
    }

    //------------------------------------------------------------------------------------------------------
    // swap
    //------------------------------------------------------------------------------------------------------
    template<typename K, std::enable_if_t<!std::is_same_v<K, value_type>>* = nullptr>
    void
    swap(vector<K>& other) noexcept
    {
        _sizes.resize(other.num_dimensions());
        std::copy(other.size().begin(), other.size().end(), _sizes.begin());

        _strides.resize(other.num_dimensions());
        std::copy(other.strides().begin(), other.strides().end(), _strides.begin());

        _values.resize(num_values());
        for (size_type i = 0; i < num_values(); ++i)
        {
            K temp = static_cast<K>(_values[i]);
            _values[i] = static_cast<value_type>(other[i]);
            other[i]   = std::move(temp);
        }
    }

    template<typename K, std::enable_if_t<!std::is_same_v<K, value_type>>* = nullptr>
    void
    swap(vector<K>&& other) noexcept
    {
        _sizes.resize(other.num_dimensions());
        std::copy(other.size().begin(), other.size().end(), _sizes.begin());

        _strides.resize(other.num_dimensions());
        std::copy(other.strides().begin(), other.strides().end(), _strides.begin());

        _values.resize(num_values());
        for (size_type i = 0; i < num_values(); ++i)
        {
            _values[i] = static_cast<value_type>(std::move(other[i]));
        }
    }

    void
    swap(self_type& other)
    {
        std::swap(_sizes, other._sizes);
        std::swap(_strides, other._strides);
        std::swap(_values, other._values);
    }

    void
    swap(self_type&& other)
    {
        _sizes   = std::move(other._sizes);
        _strides = std::move(other._strides);
        _values  = std::move(other._values);
    }

    //------------------------------------------------------------------------------------------------------
    // compare
    //------------------------------------------------------------------------------------------------------
  private:
    template<typename K>
    [[nodiscard]] bool
    _sizes_match(const vector<K>& other) const
    {
        if (num_dimensions() != other.num_dimensions())
        {
            return false;
        }

        for (unsigned int i = 0; i < num_dimensions(); ++i)
        {
            if (size(i) != other.size(i))
            {
                return false;
            }
        }

        return true;
    }

  public:

    //------------------------------------------------------------------------------------------------------
    // compare
    //------------------------------------------------------------------------------------------------------
    template<typename K>
    [[nodiscard]] bool
    _compare_data_vectors(const vector<K>& other, std::function<bool(const_reference, typename vector<K>::const_reference)> comp) const
    {
        if (!_sizes_match(other))
        {
            return false;
        }

        bool valid = true;

        for (unsigned int i = 0; i < num_values(); ++i)
        {
            valid &= comp(operator[](i), other[i]);
        }

        return valid;
    }

    template<typename K>
    [[nodiscard]] bool
    operator==(const vector<K>& other) const
    {
        if constexpr (!std::is_convertible_v<value_type, K> || !std::is_convertible_v<K, value_type>)
        {
            return false;
        }
        else
        {
            constexpr auto comp = [](const_reference x, typename vector<K>::const_reference y) -> bool
            {
                return x == y;
            };

            return _compare_data_vectors(other, comp);
        }
    }

    template<typename K>
    [[nodiscard]] bool
    operator<(const vector<K>& other) const
    {
        static_assert(std::is_convertible_v<value_type, K> && std::is_convertible_v<K, value_type>);

        if (num_values() != other.num_values())
        {
            return num_values() < other.num_values();
        }

        constexpr auto comp = [](const_reference x, typename vector<K>::const_reference y) -> bool
        {
            return x < y;
        };

        return _compare_data_vectors(other, comp);
    }

    template<typename K>
    [[nodiscard]] ND_FORCE_INLINE bool
    operator!=(const vector<K>& other) const
    {
        return !operator==(other);
    }

    template<typename K>
    [[nodiscard]] ND_FORCE_INLINE bool
    operator<=(const vector<K>& other) const
    {
        return operator<(other) || operator==(other);
    }

    template<typename K>
    [[nodiscard]] ND_FORCE_INLINE bool
    operator>(const vector<K>& other) const
    {
        return !operator<=(other);
    }

    template<typename K>
    [[nodiscard]] ND_FORCE_INLINE bool
    operator>=(const vector<K>& other) const
    {
        return !operator<(other);
    }

    //------------------------------------------------------------------------------------------------------
    // to string
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] std::string
    to_string() const
    {
        std::stringstream s;

        if (num_dimensions() == 1)
        {
            s << "[";

            for (size_type i = 0; i < num_values(); ++i)
            {
                s << operator[](i);

                if (i < num_values() - 1)
                {
                    s << ", ";
                }
            }

            s << "]";
        }
        else if (num_dimensions() == 2)
        {
            s << "[";

            for (size_type y = 0; y < size(1); ++y)
            {
                if (y != 0)
                {
                    s << " ";
                }

                s << "[";

                for (size_type x = 0; x < size(0); ++x)
                {
                    s << at_grid(x, y);

                    if (x < size(0) - 1)
                    {
                        s << ", ";
                    }
                }

                s << "]";

                if (y < size(1) - 1)
                {
                    s << "\n";
                }
            }

            s << "]";
        }
        else
        {
            s << "[";

            for (size_type i = 0; i < num_values(); ++i)
            {
                const auto gid = list_to_grid_id(i);
                s << "(";
                for (size_type k = 0; k < gid.size(); ++k)
                {
                    s << gid[k];
                    if (k < gid.size() - 1)
                    {
                        s << ",";
                    }
                }
                s << ")=";

                s << operator[](i);

                if (i < num_values() - 1)
                {
                    s << ", ";
                }
            }

            s << "]";
        }

        return s.str();
    }
}; // class vector
} // namespace nd

//------------------------------------------------------------------------------------------------------
// external stream operator
//------------------------------------------------------------------------------------------------------
template<typename T>
[[maybe_unused]] std::ostream&
operator<<(std::ostream& o, const nd::vector<T>& v)
{
    o << v.to_string();
    return o;
}

//------------------------------------------------------------------------------------------------------
// external swap
//------------------------------------------------------------------------------------------------------
template<typename T, typename K>
ND_FORCE_INLINE inline void
swap(nd::vector<T>& a, nd::vector<K>& b) noexcept
{
    a.swap(b);
}

template<typename T, typename K>
ND_FORCE_INLINE inline void
swap(nd::vector<T>&& a, nd::vector<K>& b) noexcept
{
    b.swap(std::move(a));
}

template<typename T, typename K>
ND_FORCE_INLINE inline void
swap(nd::vector<T>& a, nd::vector<K>&& b) noexcept
{
    a.swap(std::move(b));
}

#endif //__ND_VECTOR_H__8945u23895cuifnui34nf892348923m98r