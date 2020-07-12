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

#ifndef __ND_ARRAY_H__dfneluirgneriugeuivnjisdjfkjds
#define __ND_ARRAY_H__dfneluirgneriugeuivnjisdjfkjds

#include <array>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#if !defined(__GNUC__) || defined(__MINGW32__)
  #define ND_FORCE_INLINE __forceinline
#else // IF __GNUC__
  #define ND_FORCE_INLINE __attribute__((always_inline))
#endif // __GNUC__

//====================================================================================================
//===== class array
//====================================================================================================
namespace nd
{
template<typename TValue, std::size_t... TSizes>
class array
{
    //------------------------------------------------------------------------------------------------------
    // assertions
    //------------------------------------------------------------------------------------------------------
    static_assert(sizeof...(TSizes) > 0, "template sizes are missing");
    static_assert(((TSizes > 0) && ...), "all sizes must be greater than 0");

    //------------------------------------------------------------------------------------------------------
    // definitions
    //------------------------------------------------------------------------------------------------------
  public:
    [[nodiscard]] ND_FORCE_INLINE static constexpr std::size_t
    num_dimensions() noexcept
    {
        return sizeof...(TSizes);
    }

    [[nodiscard]] ND_FORCE_INLINE static constexpr std::size_t
    num_values() noexcept
    {
        return (TSizes * ...);
    }

    using self_type = array<TValue, TSizes...>;
    using value_type = TValue;
    using data_container_type = std::array<value_type, num_values()>;
    using size_type = std::size_t;
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
    data_container_type _values;

    //------------------------------------------------------------------------------------------------------
    // helpers
    //------------------------------------------------------------------------------------------------------
  private:
    [[nodiscard]] static constexpr data_container_type
    _constant_array(value_type c) noexcept
    {
        data_container_type res{};

        for (reference x : res)
        {
            x = c;
        }

        return res;
    }

    [[nodiscard]] static constexpr data_container_type
    _default_init() noexcept
    {
        data_container_type res{};

        for (reference x : res)
        {
            x = value_type();
        }

        return res;
    }

    template<typename TIndexAccessible>
    [[nodiscard]] static constexpr data_container_type
    _copy_array(TIndexAccessible&& arr) noexcept
    {
        data_container_type res{};

        for (std::size_t i = 0; i < res.size(); ++i)
        {
            res[i] = arr[i];
        }

        return res;
    }

    //------------------------------------------------------------------------------------------------------
    // ctor
    //------------------------------------------------------------------------------------------------------
  public:
    // used for arithmetic types like string
    template<typename T = value_type, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
    ND_FORCE_INLINE constexpr
    array() noexcept :
        _values{_constant_array(0)}
    { /* do nothing */ }

    // used for non-arithmetic types like string
    template<typename T = value_type, std::enable_if_t<!std::is_arithmetic_v<T>>* = nullptr>
    ND_FORCE_INLINE constexpr
    array() noexcept :
        _values{_default_init()}
    { /* do nothing */ }

    ND_FORCE_INLINE constexpr array(const self_type& other) noexcept:
        _values{_copy_array(other)}
    { /* do nothing */ }

    ND_FORCE_INLINE constexpr array(self_type&& other) noexcept:
        _values{_copy_array(std::move(other))}
    { /* do nothing */ }

    template<typename TIndexAccessible, std::enable_if_t<std::is_class_v<std::decay_t<TIndexAccessible>> && !std::is_same_v<std::decay_t<TIndexAccessible>, value_type>>* = nullptr>
    ND_FORCE_INLINE constexpr
    array(const TIndexAccessible& other) noexcept :
        _values{_copy_array(other)}
    { /* do nothing */ }

    template<typename... TValues, std::enable_if_t<sizeof...(TValues) == num_values() && std::conjunction_v<std::is_convertible<std::decay_t<TValues>, value_type>...>>* = nullptr>
    ND_FORCE_INLINE constexpr
    array(TValues&& ... values) noexcept :
        _values{static_cast<value_type>(std::forward<TValues>(values))...}
    { /* do nothing */ }

    //------------------------------------------------------------------------------------------------------
    // dtor
    //------------------------------------------------------------------------------------------------------
    ND_FORCE_INLINE ~array() noexcept = default;

    //------------------------------------------------------------------------------------------------------
    // assignment
    //------------------------------------------------------------------------------------------------------
    template<typename T, std::enable_if_t<!std::is_same_v<T, value_type>>* = nullptr>
    [[maybe_unused]] ND_FORCE_INLINE constexpr self_type&
    operator=(array<T, TSizes...>& other) noexcept
    {
        for (size_type i = 0; i < num_values(); ++i)
        {
            _values[i] = static_cast<value_type>(other[i]);
        }

        return *this;
    }

    [[maybe_unused]] ND_FORCE_INLINE constexpr self_type&
    operator=(const self_type&) noexcept = default;

    [[maybe_unused]] ND_FORCE_INLINE constexpr self_type&
    operator=(self_type&&) noexcept = default;

    //------------------------------------------------------------------------------------------------------
    // cast
    //------------------------------------------------------------------------------------------------------
    template<typename T>
    [[nodiscard]] ND_FORCE_INLINE constexpr array<T, TSizes...>
    cast() const noexcept
    {
        static_assert(std::is_convertible_v<value_type, T>, "cannot cast types");
        return array<T, TSizes...>(*this);
    }

    //------------------------------------------------------------------------------------------------------
    // size
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE static constexpr std::array<size_type, num_dimensions()>
    size() noexcept
    {
        return std::array<size_type, num_dimensions()>{{TSizes...}};
    }

    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    size(size_type dimId) noexcept
    {
        return size()[dimId];
    }

    //------------------------------------------------------------------------------------------------------
    // empty
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE static constexpr bool
    empty() noexcept
    {
        return num_values() == 0;
    }

    //------------------------------------------------------------------------------------------------------
    // stride
    //------------------------------------------------------------------------------------------------------
  private:
    template<typename... Sizes>
    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    __stride_of_dim(size_type skip, size_type s0, Sizes... s) noexcept
    {
        if (skip > 0)
        {
            if constexpr (sizeof...(Sizes) == 0)
            {
                return 1U;
            }
            else
            {
                return __stride_of_dim(skip - 1, s...);
            }
        }
        else
        {
            return s0 * (s * ... * 1U);
        }
    }

    template<typename... Sizes>
    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    _stride_of_dim(size_type dimId, Sizes... s) noexcept
    {
        return __stride_of_dim(dimId + 1, s...);
    }

    template<std::size_t... Is>
    [[nodiscard]] ND_FORCE_INLINE static constexpr std::array<size_type, num_dimensions()>
    _strides(std::index_sequence<Is...>) noexcept
    {
        return std::array<size_type, num_dimensions()>{stride(Is)...};
    }

  public:

    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    stride(size_type dimId) noexcept
    {
        return _stride_of_dim(dimId, TSizes...);
    }

    [[nodiscard]] ND_FORCE_INLINE static constexpr std::array<size_type, num_dimensions()>
    strides() noexcept
    {
        return _strides(std::make_index_sequence<num_dimensions()>());
    }

    //------------------------------------------------------------------------------------------------------
    // list id / grid id conversion
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] static constexpr std::array<size_type, num_dimensions()>
    list_to_grid_id(size_type lid) noexcept
    {
        assert(lid < num_values());

        std::array<size_type, num_dimensions()> gid{};

        constexpr auto str = strides();

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
    template<typename TIndexAccessible, std::size_t... Is>
    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    _grid_to_list_id_index(TIndexAccessible&& gid, std::index_sequence<Is...>) noexcept
    {
        return 0U + (... + (stride(Is) * gid[Is]));
    }

    template<std::size_t I, typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE static constexpr size_type
    _grid_to_list_id_pack(size_type gid0, Ids... gid) noexcept
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
    [[nodiscard]] static constexpr size_type
    grid_to_list_id(Ids&& ... ids) noexcept
    {
        assert(is_valid_ids(ids...));

        constexpr bool isIndexPack           = sizeof...(Ids) == num_dimensions() && std::conjunction_v<std::is_integral<std::remove_reference_t<Ids>>...>;
        constexpr bool isPlainArrayOrPointer = sizeof...(Ids) == 1 && (std::conjunction_v<std::is_array<std::remove_reference_t<Ids>>...> || std::conjunction_v<std::is_pointer<std::remove_reference_t<Ids>>...>);
        constexpr bool isClass               = sizeof...(Ids) == 1 && std::conjunction_v<std::is_class<std::remove_reference_t<Ids>>...>;

        static_assert(isIndexPack || isPlainArrayOrPointer || isClass, "Invalid number of arguments! "
                                                                       "Either provide N individual integral indices "
                                                                       "or provide a plain C-array / pointer / index[]-accessible class "
                                                                       "containing N indices! "
                                                                       "( N = num_dimensions() )");

        if constexpr (isIndexPack)
        {
            return _grid_to_list_id_pack<0>(std::forward<Ids>(ids)...);
        }
        else if constexpr (isPlainArrayOrPointer || isClass)
        {
            return _grid_to_list_id_index(std::forward<Ids>(ids)..., std::make_index_sequence<num_dimensions()>());
        }

        return 0;
    }

    //------------------------------------------------------------------------------------------------------
    // data
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE constexpr data_container_type&
    data()& noexcept
    {
        return _values;
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr const data_container_type&
    data() const& noexcept
    {
        return _values;
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr data_container_type&&
    data()&& noexcept
    {
        return std::move(_values);
    }

    //------------------------------------------------------------------------------------------------------
    // operator[]
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    operator[](size_type lid) noexcept
    {
        assert(lid < num_values());
        return _values[lid];
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    operator[](size_type lid) const noexcept
    {
        assert(lid < num_values());
        return _values[lid];
    }

    //------------------------------------------------------------------------------------------------------
    // at list id
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    at_list(size_type id)
    {
        if (id >= num_values())
        {
            throw std::out_of_range("trying to access array[" + std::to_string(id) + "] with size " + std::to_string(num_values()));
        }

        return _values[id];
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    at_list(size_type id) const
    {
        if (id >= num_values())
        {
            throw std::out_of_range("trying to access array[" + std::to_string(id) + "] with size " + std::to_string(num_values()));
        }

        return _values[id];
    }

    template<std::size_t Id>
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    at_list() noexcept
    {
        static_assert(Id < num_values()); return _values[Id];
    }

    template<std::size_t Id>
    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    at_list() const noexcept
    {
        static_assert(Id < num_values()); return _values[Id];
    }

    //------------------------------------------------------------------------------------------------------
    // helper: ids are valid
    //------------------------------------------------------------------------------------------------------
  private:
    template<typename T, std::size_t... Is>
    [[nodiscard]] ND_FORCE_INLINE static constexpr bool
    _is_valid_ids(T&& idsObject, std::index_sequence<Is...>) noexcept
    {
        return is_valid_ids(idsObject[Is]...);
    }

  public:

    template<typename... Ids>
    [[nodiscard]] static constexpr bool
    is_valid_ids(Ids&& ... ids) noexcept
    {
        constexpr bool isIndexPack           = sizeof...(Ids) == num_dimensions() && std::conjunction_v<std::is_integral<std::remove_reference_t<Ids>>...>;
        constexpr bool isPlainArrayOrPointer = sizeof...(Ids) == 1 && (std::conjunction_v<std::is_array<std::remove_reference_t<Ids>>...> || std::conjunction_v<std::is_pointer<std::remove_reference_t<Ids>>...>);
        constexpr bool isClass               = sizeof...(Ids) == 1 && std::conjunction_v<std::is_class<std::remove_reference_t<Ids>>...>;

        static_assert(isIndexPack || isPlainArrayOrPointer || isClass, "Invalid number of arguments! "
                                                                       "Either provide N individual integral indices "
                                                                       "or provide a plain C-array / pointer / index[]-accessible class "
                                                                       "containing N indices! "
                                                                       "( N = num_dimensions() )");

        if constexpr (isIndexPack)
        {
            return ((ids >= 0 && static_cast<std::common_type_t<Ids, decltype(TSizes)>>(ids) < static_cast<std::common_type_t<Ids, decltype(TSizes)>>(TSizes)) && ... && true);
        }
        else if constexpr (isPlainArrayOrPointer || isClass)
        {
            return _is_valid_ids(std::forward<Ids>(ids)..., std::make_index_sequence<num_dimensions()>());
        }

        return false;
    }

  public:

    //------------------------------------------------------------------------------------------------------
    // operator()
    //------------------------------------------------------------------------------------------------------
    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    operator()(Ids&& ... ids) noexcept
    {
        return at_grid(std::forward<Ids>(ids)...);
    }

    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    operator()(Ids&& ... ids) const noexcept
    {
        return at_grid(std::forward<Ids>(ids)...);
    }

    //------------------------------------------------------------------------------------------------------
    // at grid
    //------------------------------------------------------------------------------------------------------
    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    at_grid(Ids&& ... ids) noexcept
    {
        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    template<typename... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    at_grid(Ids&& ... ids) const noexcept
    {
        return _values[grid_to_list_id(std::forward<Ids>(ids)...)];
    }

    template<std::size_t... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    at_grid() noexcept
    {
        static_assert(sizeof...(Ids) == num_dimensions());
        static_assert(((Ids < TSizes) && ... && true));

        constexpr const size_type lid = grid_to_list_id(Ids...);
        return _values[lid];
    }

    template<std::size_t... Ids>
    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    at_grid() const noexcept
    {
        static_assert(sizeof...(Ids) == num_dimensions());
        static_assert(((Ids < TSizes) && ... && true));

        constexpr const size_type lid = grid_to_list_id(Ids...);
        return _values[lid];
    }

    //------------------------------------------------------------------------------------------------------
    // front / back
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    front() noexcept
    {
        return _values.front();
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    front() const noexcept
    {
        return _values.front();
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr reference
    back() noexcept
    {
        return _values.back();
    }

    [[nodiscard]] ND_FORCE_INLINE constexpr const_reference
    back() const noexcept
    {
        return _values.back();
    }

    //------------------------------------------------------------------------------------------------------
    // iterators
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] ND_FORCE_INLINE iterator
    begin() noexcept
    {
        return _values.begin();
    }

    [[nodiscard]] ND_FORCE_INLINE const_iterator
    begin() const noexcept
    {
        return _values.begin();
    }

    [[nodiscard]] ND_FORCE_INLINE iterator
    end() noexcept
    {
        return _values.end();
    }

    [[nodiscard]] ND_FORCE_INLINE const_iterator
    end() const noexcept
    {
        return _values.end();
    }

    [[nodiscard]] ND_FORCE_INLINE reverse_iterator
    rbegin() noexcept
    {
        return _values.rbegin();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reverse_iterator
    rbegin() const noexcept
    {
        return _values.rbegin();
    }

    [[nodiscard]] ND_FORCE_INLINE reverse_iterator
    rend() noexcept
    {
        return _values.rend();
    }

    [[nodiscard]] ND_FORCE_INLINE const_reverse_iterator
    rend() const noexcept
    {
        return _values.rend();
    }

    //------------------------------------------------------------------------------------------------------
    // set values
    //------------------------------------------------------------------------------------------------------
    template<typename... TValues>
    ND_FORCE_INLINE constexpr void
    set_values(TValues&& ... values)
    {
        static_assert(sizeof...(TValues) == num_values(), "invalid number of arguments");
        _values = {static_cast<value_type>(std::forward<TValues>(values))...};
    }

    constexpr void
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
    swap(array<K, TSizes...>& other) noexcept
    {
        for (size_type i = 0; i < num_values(); ++i)
        {
            K temp = static_cast<K>(_values[i]);
            _values[i] = static_cast<value_type>(other[i]);
            other[i]   = std::move(temp);
        }
    }

    template<typename K, std::enable_if_t<!std::is_same_v<K, value_type>>* = nullptr>
    void
    swap(array<K, TSizes...>&& other) noexcept
    {
        for (size_type i = 0; i < num_values(); ++i)
        {
            _values[i] = static_cast<value_type>(other[i]);
        }
    }

    ND_FORCE_INLINE void
    swap(self_type& other) noexcept
    {
        std::swap(_values, other._values);
    }

    ND_FORCE_INLINE void
    swap(self_type&& other) noexcept
    {
        std::swap(_values, other._values);
    }

    //------------------------------------------------------------------------------------------------------
    // compare
    //------------------------------------------------------------------------------------------------------
    template<typename K, std::size_t... S>
    [[nodiscard]] constexpr bool
    operator==(const array<K, S...>& other) const noexcept
    {
        if constexpr (num_dimensions() != other.num_dimensions())
        {
            return false;
        }
        else if constexpr (((S != TSizes) || ...))
        {
            return false;
        }
        else if constexpr (!std::is_convertible_v<value_type, K> || !std::is_convertible_v<K, value_type>)
        {
            return false;
        }
        else
        {
            for (size_type i = 0; i < num_values(); ++i)
            {
                if (_values[i] != other[i])
                {
                    return false;
                }
            }

            return true;
        }
    }

    template<typename K, std::size_t... S>
    [[nodiscard]] constexpr bool
    operator<(const array<K, S...>& other) const noexcept
    {
        static_assert(num_dimensions() == other.num_dimensions(), "less operator is only defined for arrays with same dimensionality!");
        static_assert(((TSizes == S) && ...), "less operator is only defined for same-sized arrays");

        for (size_type i = 0; i < num_values(); ++i)
        {
            if (_values[i] != other[i])
            {
                return _values[i] < other[i];
            }
        }

        return false;
    }

    template<typename K, std::size_t... S>
    [[nodiscard]] ND_FORCE_INLINE constexpr bool
    operator!=(const array<K, S...>& other) const noexcept
    {
        return !operator==(other);
    }

    template<typename K, std::size_t... S>
    [[nodiscard]] ND_FORCE_INLINE constexpr bool
    operator>(const array<K, S...>& other) const noexcept
    {
        return !operator<=(other);
    }

    template<typename K, std::size_t... S>
    [[nodiscard]] ND_FORCE_INLINE constexpr bool
    operator>=(const array<K, S...>& other) const noexcept
    {
        return !operator<(other);
    }

    template<typename K, std::size_t... S>
    [[nodiscard]] ND_FORCE_INLINE constexpr bool
    operator<=(const array<K, S...>& other) const noexcept
    {
        return operator<(other) || operator==(other);
    }

    //------------------------------------------------------------------------------------------------------
    // to string
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] std::string
    to_string() const
    {
        std::stringstream s;

        if constexpr (num_dimensions() == 1)
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
        else if constexpr (num_dimensions() == 2)
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

    //------------------------------------------------------------------------------------------------------
    // factory
    //------------------------------------------------------------------------------------------------------
    [[nodiscard]] static constexpr self_type
    Constant(const value_type& constant) noexcept
    {
        self_type res{};
        res.fill(constant);
        return res;
    }

    [[nodiscard]] ND_FORCE_INLINE static constexpr self_type
    Zero() noexcept
    {
        return Constant(static_cast<value_type>(0));
    }

    [[nodiscard]] ND_FORCE_INLINE static constexpr self_type
    One() noexcept
    {
        return Constant(static_cast<value_type>(1));
    }
}; // class array
} // namespace nd

//------------------------------------------------------------------------------------------------------
// external stream operator
//------------------------------------------------------------------------------------------------------
template<typename T, std::size_t... S>
[[maybe_unused]] std::ostream&
operator<<(std::ostream& o, const nd::array<T, S...>& v)
{
    o << v.to_string();
    return o;
}

//------------------------------------------------------------------------------------------------------
// external swap
//------------------------------------------------------------------------------------------------------
template<typename T, typename K, std::size_t... S>
ND_FORCE_INLINE inline void
swap(nd::array<T, S...>& a, nd::array<K, S...>& b) noexcept
{
    a.swap(b);
}

template<typename T, typename K, std::size_t... S>
ND_FORCE_INLINE inline void
swap(nd::array<T, S...>&& a, nd::array<K, S...>& b) noexcept
{
    b.swap(std::move(a));
}

template<typename T, typename K, std::size_t... S>
ND_FORCE_INLINE inline void
swap(nd::array<T, S...>& a, nd::array<K, S...>&& b) noexcept
{
    a.swap(std::move(b));
}

#undef ND_FORCE_INLINE

#endif //__ND_ARRAY_H__dfneluirgneriugeuivnjisdjfkjds
