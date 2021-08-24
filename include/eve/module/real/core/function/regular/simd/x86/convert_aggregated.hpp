//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_floating_point.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_shl.hpp>

namespace eve::detail
{
  //================================================================================================
  // Converting from aggregation of x86_128 to x86_128
  //================================================================================================
  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE wide<Out,N>
  convert_(EVE_SUPPORTS(sse2_), wide<In, N> const &v0, as<Out> const &tgt) noexcept
  requires(   std::same_as<typename wide<Out,N>::abi_type, x86_128_>
          &&  std::same_as<abi_t<In, N>, aggregated_>
          )
  {
    if constexpr( std::same_as<In,double> )
    {
      auto[l,h] = v0.slice();
      auto lc = convert(l, tgt);
      auto hc = convert(h, tgt);

      auto cc = bit_cast( wide<std::uint32_t,N>(_mm_bslli_si128( bit_cast(hc, as<wide<std::uint32_t,N>>()), 2*sizeof(Out)))
                        , as<wide<Out,N>>()
                        );
      return cc | lc;
    }
    /*
    // int16x8 => int32x8
    else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && sizeof(Out) == 4)
    {
      puts("LA");
      // We slice the shortx16 int shortsx8
      auto[l,h] = v0.slice();

      std::cout << "l: " << l << "\n";
      std::cout << "h: " << h << "\n";
      // Remove the higher bits that will cause unwanted saturation
      l = static_cast<In>(0x00FFU);
      h = static_cast<In>(0x00FFU);
      std::cout << "l': " << l << "\n";
      std::cout << "h': " << h << "\n";
      wide<Out,N> r(_mm_packus_epi16(l,h));
      std::cout << "r: " << r << "\n";
      // Pack as bunch of bytes that can't saturate anyway
      return _mm_packus_epi16(l,h);
    }
    // intx8 -> shortx8
    else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) )
    {
      if constexpr(sizeof(Out) == 2)
      {
        auto[l,h] = v0.slice();

        if constexpr( current_api >= sse4_1 )
        {
          l &= static_cast<In>(0x0000FFFFU);
          h &= static_cast<In>(0x0000FFFFU);

          return _mm_packus_epi32(l,h);
        }
        else if constexpr( current_api >= ssse3 )
        {
          l &= static_cast<In>(0x0000FFFFU);
          h &= static_cast<In>(0x0000FFFFU);
          return _mm_hadd_epi16(l,h);
        }
        else
        {
          l = _mm_shufflehi_epi16(l, _MM_SHUFFLE(2,0,2,0));
          l = _mm_shufflelo_epi16(l, _MM_SHUFFLE(2,0,2,0));
          l = _mm_shuffle_epi32  (l, _MM_SHUFFLE(2,0,2,0));

          h = _mm_shufflehi_epi16(h, _MM_SHUFFLE(2,0,2,0));
          h = _mm_shufflelo_epi16(h, _MM_SHUFFLE(2,0,2,0));
          h = _mm_shuffle_epi32  (h, _MM_SHUFFLE(2,0,2,0));

          return bit_cast( _mm_shuffle_ps ( bit_cast(l, as<as_floating_point_t<decltype(l)>>())
                                          , bit_cast(h, as<as_floating_point_t<decltype(h)>>())
                                          , _MM_SHUFFLE(1,0,1,0)
                                          )
                                , as<wide<Out>>()
                                );
        }
      }
      else
      {
        return convert(convert(v0, as<downgrade_t<In>>()), as<Out>());
      }
    }
      */
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }
}
