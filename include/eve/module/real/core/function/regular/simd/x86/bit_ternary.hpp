//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/bit_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  template<int k, integral_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_ternary_(EVE_SUPPORTS(avx512_),
                                          wide<T, N> const &x,
                                          wide<T, N> const &y,
                                          wide<T, N> const &z,
                                          std::integral_constant<int, k> const & ik) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
//    constexpr bool i = c && category::integer_;

          if constexpr( c == category::int64x8 ) return _mm512_ternarylogic_epi64(x, y, z, k);
    else  if constexpr( c == category::int64x4 ) return _mm256_ternarylogic_epi64(x, y, z, k);
    else  if constexpr( c == category::int64x2 ) return _mm_ternarylogic_epi64(x, y, z, k);
    else  if constexpr( c == category::int32x16) return _mm512_ternarylogic_epi32(x, y, z, k);
    else  if constexpr( c == category::int32x8 ) return _mm256_ternarylogic_epi32(x, y, z, k);
    else  if constexpr( c == category::int32x4 ) return _mm_ternarylogic_epi32(x, y, z, k);
    else  return bit_ternary_(EVE_RETARGET(cpu_), x, y, z, ik);
  }
}
