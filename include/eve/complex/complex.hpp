//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/function/real.hpp>
#include <eve/function/imag.hpp>
#include <eve/product_type.hpp>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-aware complex number type
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
      os << get<0>(z);
      if(auto i = get<1>(z); i < 0) os << " - " << -i; else os << " + " << i;
      return os << " * i";
    }

    template<like<complex> T>
    friend EVE_FORCEINLINE auto tagged_dispatch(eve::tag::real_ const&, T const &a) noexcept
    {
      return get<0>(a);
    }

    template<like<complex> T>
    friend EVE_FORCEINLINE auto tagged_dispatch(eve::tag::imag_ const&, T const &a) noexcept
    {
      return get<1>(a);
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}