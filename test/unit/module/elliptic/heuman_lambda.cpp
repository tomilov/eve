//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/heuman_lambda.hpp>
#include <boost/math/special_functions/heuman_lambda.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>

#include <cmath>

EVE_TEST_TYPES("Check eve::heuman_lambda return type",
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS(eve::heuman_lambda(T(0), T(0)), T);
}


EVE_TEST_TYPES( "Check eve::heuman_lambda behavior two parameters"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  if constexpr( eve::platform::supports_invalids )
  {
   TTS_IEEE_EQUAL(eve::heuman_lambda(eve::pio_4(as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
   TTS_ULP_EQUAL(eve::heuman_lambda(eve::pio_2(as<T>()), T(1)) , eve::one(eve::as<T>()), 0.5);
   TTS_ULP_EQUAL(eve::heuman_lambda(eve::pio_2(as<T>()), T(-1)), eve::one(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_2(as<T>()), T( 0.)),  eve::one(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_2(as<T>()), T( 0.5)), eve::one(eve::as<T>()), 4);
  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_2(as<T>()), T( 0.9)), eve::one(eve::as<T>()), 4.55);

  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_4(as<T>()), T( 0.)),  T(boost::math::heuman_lambda(v_t(0)  , eve::pio_4(as<v_t>()))), 1.0);
  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_4(as<T>()), T( 0.5)), T(boost::math::heuman_lambda(v_t(0.5), eve::pio_4(as<v_t>()))), 2.0);
  TTS_ULP_EQUAL( eve::heuman_lambda(eve::pio_4(as<T>()), T( 0.9)), T(boost::math::heuman_lambda(v_t(0.9), eve::pio_4(as<v_t>()))), 1.5);

}
