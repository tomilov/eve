//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup comparisons
  //! @{
  //! @var is_greater
  //!
  //! @brief Callable object computing the "greater than" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_greater.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "greater than" predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [elementwise](@ref glossary_elementwise) comparison test result
  //!between `x` and `y`. The infix notation `x > y` can also be used.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //!@warning
  //!   Although the infix notation with `>` is supported, the `>` operator on
  //!   standard scalar types is the original one and so returns bool result, not `logical`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_greater
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_greater[cond](x, y)` is equivalent to
  //! `if_else(cond,is_greater(x, y),false(as(is_greater(x, y))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `definitely`
  //!
  //!     **Required header:** `#include <eve/function/fuzzy/is_greater.hpp>`
  //!
  //!     The expression `definitely(is_greater)(x, y, t)` where `x` and `y` must be
  //!      floating point values, evals to true if and only if `x` is definitely greater than `y`.
  //!      This means that:
  //!
  //!      - if `t` is a floating_value then  \f$x > y + t \max(|x|, |y|)\f$
  //!      - if `t` is a positive integral_value then \f$x > \mbox{next}(y, t)\f$;
  //!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/is_greater.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_greater_, is_greater);

  namespace detail
  {
    template<value T, value U>
    EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a > b);
      else                                                return a > b;
    }

    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, real_value U, real_value V>
    EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
    {
      return logical_mask_op(cond, is_greater, u, v);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/arithmetic/regular/impl/simd/x86/is_greater.hpp>
#endif
