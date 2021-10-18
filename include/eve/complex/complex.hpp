//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/product_type.hpp>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-aware complex number types
  //!
  //! **Required header:** `#include <eve/complex/complex.hpp>`
  //!
  //! @tparam Type  Floating-point type to use as complex base type
  //================================================================================================
  template<floating_real_scalar_value Type>
  struct complex : eve::struct_support<complex<Type>, Type, Type>
  {
    // No ordering on complex by default
    using eve_disable_ordering = void;
    using parent               = eve::struct_support<complex<Type>, Type, Type>;

    //! @brief Underlying floating type
    using value_type = Type;

    //! @brief Default constructor
    complex() {}

    //! @brief Construct an eve::complex from a real and imaginary part
    //! @param r Real part of the complex to be constructed
    //! @param i Imaginary part of the complex to be constructed
    complex(Type r, Type i = {}) : parent(r,i) {}

    //! @brief Inserts a eve::complex into a output stream
    friend std::ostream& operator<<(std::ostream& os, complex<Type> const& z) noexcept
    {
      auto i = get<1>(z);
      return os << get<0>(z) << (i < 0 ? " - " : " + " ) << i << " * i";
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}