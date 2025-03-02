//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_nltz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_nltz", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t = eve::as_logical_t<T>;
  auto std_is_nltz = tts::vectorize<l_t>( [](auto e) { return !(e < v_t(0)); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_is_nltz, eve::is_nltz);
}
