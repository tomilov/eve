//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/bit_ternary.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_not.hpp>


EVE_TEST_TYPES("Check eve::bit_ternary return type"
              , eve::test::simd::integers)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<T, unsigned>;
  constexpr std::integral_constant<int, 0x0f>  ik;
  TTS_EXPR_IS(eve::bit_ternary( T() ,   T() ,   T(), ik), T);
  TTS_EXPR_IS(eve::bit_ternary(  T() ,   T() , v_t() , ik), T);
  TTS_EXPR_IS(eve::bit_ternary(  T() , v_t() ,   T() , ik), T);
  TTS_EXPR_IS(eve::bit_ternary(i_t() ,   T() ,   T() , ik), i_t);
  TTS_EXPR_IS(eve::bit_ternary(i_t() ,   T() , v_t() , ik), i_t);
  TTS_EXPR_IS(eve::bit_ternary(i_t() , v_t() ,   T() , ik), i_t);
};

EVE_TEST_TYPES( "Check eve::bit_ternary, ik behavior"
              , eve::test::simd::integers)
<typename T>(eve::as<T>)
{
  using eve::as;
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;
  using v_t =  eve::element_type_t<T>;

  std::uint64_t base  = 0xF5555552F552F5F2ULL;
  i_t           imask = static_cast<i_t>(base & std::uint64_t(~vi_t(0)));
  T          mask  = eve::bit_cast(imask, as(T()));
  constexpr std::integral_constant<int, 0x0f>  ik;

  TTS_EQUAL( eve::bit_ternary( imask, eve::allbits(as<T>()) , T( 0 )          , ik), eve::bit_not(imask) );
  TTS_EQUAL( eve::bit_ternary( imask, eve::allbits(as<v_t>()), T( 0 )         , ik), eve::bit_not(imask) );
TTS_EQUAL( eve::bit_ternary( imask, eve::allbits(as<T>()) , eve::zero(as<v_t>()), ik), eve::bit_not(imask) );

  TTS_EQUAL( eve::bit_ternary( mask, eve::allbits(as<T>())  , T( 0 )          , ik), eve::bit_not(mask));
  TTS_EQUAL( eve::bit_ternary( mask, eve::allbits(as<v_t>()) , T( 0 )         , ik), eve::bit_not(mask));
  TTS_EQUAL( eve::bit_ternary( mask, eve::allbits(as<T>())  , eve::zero(as<v_t>()), ik), eve::bit_not(mask));
};
