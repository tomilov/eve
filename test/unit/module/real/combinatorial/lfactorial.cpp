//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/lfactorial.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::lfactorial"
              , eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    TTS_EXPR_IS( eve::lfactorial(T())                       , d_t);
    TTS_EXPR_IS( eve::lfactorial(v_t())                     , double );
  }
  else
  {
    TTS_EXPR_IS( eve::lfactorial(T())                       , T);
    TTS_EXPR_IS( eve::lfactorial(v_t())                     , v_t );
  }
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::lfactorial on wide"
        , eve::test::simd::all_types

         )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  if constexpr(eve::integral_value<T>)
  {
  using v_t = eve::element_type_t<T>;
    TTS_EQUAL(eve::lfactorial(T(10)) , eve::log(d_t(3628800)));
    TTS_EQUAL(eve::lfactorial(T( 5)) , eve::log(d_t(120)));
    TTS_EQUAL(eve::lfactorial(T(0))  , eve::log(d_t(1)));
    TTS_EQUAL(eve::lfactorial(T(1))  , eve::log(d_t(1)));
    if constexpr(sizeof(v_t) > 1)
      TTS_EQUAL(eve::lfactorial(T(200)), eve::lgamma(d_t(201)));
  }
  else
  {
    TTS_EQUAL(eve::lfactorial(T(10)) , eve::log(T(3628800)));
    TTS_EQUAL(eve::lfactorial(T( 5)) , eve::log(T(120)));
    TTS_EQUAL(eve::lfactorial(T(0))  , eve::log(T(1)));
    TTS_EQUAL(eve::lfactorial(T(1))  , eve::log(T(1)));
    TTS_EQUAL(eve::lfactorial(T(200)), eve::lgamma(T(201)));
  }
};
