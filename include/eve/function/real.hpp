//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var real
  //!
  //! @brief Callable object extracting the real part of a value.
  //!
  //! **Required header:** `#include <eve/function/complex/real.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Extract the real part of its parameter                     |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const& x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `x`:  An instance of eve::value
  //!
  //! **Return value**
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/real.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(real_, real);

  namespace detail
  {
    template<real_scalar_value T>
    EVE_FORCEINLINE constexpr T real_(EVE_SUPPORTS(cpu_), T const &a) noexcept
    {
      return a;
    }
  }
}