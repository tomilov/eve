//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rshr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using I_TYPE    = eve::as_integer_t<EVE_TYPE, signed>;
  using EVE_VALUE = eve::element_type_t<EVE_TYPE>;
  using I_VALUE   = eve::as_integer_t<EVE_VALUE, signed>;
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  auto smax = I_VALUE(sizeof(EVE_VALUE)-1);
  auto smin = I_VALUE(-smax);

  auto std__rshr =  [](EVE_VALUE x,  I_VALUE y){return EVE_VALUE(y > 0 ? x >> y : x << -y); };
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<I_VALUE>(smin,smax);

  eve::bench::experiment xp;
  run<eve::bench::types<EVE_VALUE, I_VALUE>>(EVE_NAME(std__rshr) , xp, std__rshr, arg0, arg1);
  run<eve::bench::types<EVE_VALUE, I_VALUE>>(EVE_NAME(rshr) , xp, eve::rshr, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_VALUE>> (EVE_NAME(rshr) , xp, eve::rshr, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_TYPE>> (EVE_NAME(rshr) , xp, eve::rshr, arg0, arg1);


}
