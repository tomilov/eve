//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <bit>
#include <compare>
#include <cstddef>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================

  //================================================================================================
  //! @brief SIMD register cardinal type
  //!
  //! eve::fixed_lane wraps an integral power of two constant that represents the number of lanes
  //! in a given eve::simd_value type.
  //!
  //================================================================================================
  struct fixed_lane
  {
    consteval fixed_lane(std::ptrdiff_t v) : value(v)
    {
      if( !std::has_single_bit( static_cast<std::size_t>(v)) )
        throw "[eve] Lane must be a power of 2";
    }

    consteval auto operator<=>(const fixed_lane&) const noexcept = default;

    friend consteval fixed_lane operator*(fixed_lane l, int n) noexcept { return {l.value * n}; }
    friend consteval fixed_lane operator*(int n, fixed_lane l) noexcept { return {l.value * n}; }
    friend consteval fixed_lane operator/(fixed_lane l, int n) noexcept { return {l.value / n}; }

    std::ptrdiff_t const value;
  };

  template<std::ptrdiff_t N> inline constexpr fixed_lane lane{N};

  //================================================================================================
  //! @brief Cardinal type for scalar values
  //================================================================================================
  struct scalar_cardinal : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = scalar_cardinal;
    using combined_type = fixed<2>;
  };

  //================================================================================================
  //! @brief Cardinal object representing the cardinal of [scalar values](@ref eve::scalar_value)
  //================================================================================================
  inline constexpr scalar_cardinal const scalar = {};

  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  // Constant index template class
  //================================================================================================
  template<std::ptrdiff_t Index>
  struct index_t : std::integral_constant<std::ptrdiff_t, Index>
  {};

  //================================================================================================
  // Template inline object for passing index within a wide
  //================================================================================================
  template<std::ptrdiff_t N> inline constexpr auto index = index_t<N>{};

  //================================================================================================
  // Hardware-agnostic cardinal
  //================================================================================================
  namespace detail
  {
    template<typename T> using cache_line_cardinal = fixed<64 / sizeof(T)>;
  }
}
