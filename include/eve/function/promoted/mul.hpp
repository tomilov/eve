//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/mul.hpp>
#include <eve/module/real/core/function/promoted/generic/mul.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/promoted/simd/x86/mul.hpp>
#endif


#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/promoted/simd/arm/neon/mul.hpp>
#endif
