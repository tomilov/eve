//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sqr", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_sqr = tts::vectorize<T>( [](auto e) { return e*e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated(eve::sqr));
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto std_sqr = tts::vectorize<T>( [](auto e) { return eve::abs(e) > eve::sqrtvalmax(eve::as<v_t>()) ? eve::valmax(eve::as<v_t>()) : e*e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
  else
  {
    auto std_sqr = tts::vectorize<T>( [](auto e) { return e > eve::sqrtvalmax(eve::as<v_t>()) ? eve::valmax(eve::as<v_t>()) : e*e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
}
