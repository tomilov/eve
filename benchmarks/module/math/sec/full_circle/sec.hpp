//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__sec = [](auto x){return 1/std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__sec) , xp, std__sec , arg0);
  run<EVE_VALUE>(EVE_NAME(full_circle(eve::sec)) , xp, eve::full_circle(eve::sec) , arg0);
  run<EVE_TYPE> (EVE_NAME(full_circle(eve::sec)) , xp, eve::full_circle(eve::sec) , arg0);

}
