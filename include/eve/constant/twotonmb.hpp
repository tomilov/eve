//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_TWOTONMB_HPP_INCLUDED
#define EVE_CONSTANT_TWOTONMB_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(twotonmb_, twotonmb_);

  template<typename T>
  EVE_FORCEINLINE auto Twotonmb(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    if  constexpr(std::is_floating_point_v<t_t>)
    {
      if constexpr(std::is_same_v<t_t, float>) return Constant<T,0X4B000000U>();
      if constexpr(std::is_same_v<t_t, double >) return Constant<T,0X4330000000000000ULL>();
    }
    else
      return T(1); 
  }

  EVE_MAKE_NAMED_CONSTANT(twotonmb_, Twotonmb);
}

#endif
