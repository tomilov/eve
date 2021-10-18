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
  //! @var imag
  //!
  //! @brief Callable object extracting the imaginary part of a value.
  //!
  //! **Required header:** `#include <eve/function/complex/imag.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Extract the imaginary part of its parameter                |
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
  //! @godbolt{doc/complex/imag.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(imag_, imag);

  namespace detail
  {
    template<real_scalar_value T>
    EVE_FORCEINLINE constexpr T imag_(EVE_SUPPORTS(cpu_), T const &a) noexcept
    {
      return T{0};
    }
  }
}