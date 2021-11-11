//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/detail/callable.hpp>

namespace eve::detail
{
  template<typename Condition>
  struct generic_mask_add_
  {
    template<real_value U, real_value V>
    EVE_FORCEINLINE auto operator()(U const &t, V const &f) const noexcept
    requires compatible_values<U, V>
    {
      return mask_op(cond, typename callable_<tag::add_,Condition>::type{}, t, f);
    }

    Condition cond;
  };

  struct generic_add_ : detail::supports_extension<tag::add_>
                      , supports_masking<tag::add_>
  {
    friend inline std::ostream& operator<<(std::ostream& os, generic_add_ const&)
    {
      return os << "add";
    }

    //==============================================================================================
    //N parameters
    //==============================================================================================
    // template<decorator D, real_value T0, real_value ...Ts>
    // EVE_FORCEINLINE
    // common_compatible_t<T0,Ts...> operator()(D const &, T0 a0, Ts... args)  const noexcept
    //   requires (compatible_values<T0, Ts> && ...)
    // {
    //   typename callable_<tag::add_,T0>::type const add{};

    //   common_compatible_t<T0,Ts...> that(a0);
    //   ((that = D()(add)(that,args)),...);
    //   return that;
    // }

    // template<real_value T0, real_value ...Ts>
    // EVE_FORCEINLINE
    // common_compatible_t<T0,Ts...> operator()(T0 a0, Ts... args)  const noexcept
    //   requires (compatible_values<T0, Ts> && ...)
    // {
    //   typename callable_<tag::add_,T0>::type const add{};

    //   common_compatible_t<T0,Ts...> that(a0);
    //   ((that = add(that,args)),...);
    //   return that;
    // }

    template<real_value T0, real_value T1>
    EVE_FORCEINLINE auto operator()(T0 a0, T1 a1)  const noexcept
                    requires (compatible_values<T0, T1>)
    {
      common_compatible_t<T0,T1> that(a0);
      return that+=a1;
    }
  };
}
