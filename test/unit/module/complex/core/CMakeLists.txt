##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.complex.core.exe       )
add_custom_target(unit.complex.core.simd.exe  )

add_dependencies(unit.complex.simd.exe  unit.complex.core.simd.exe  )
add_dependencies(unit.complex.core.exe  unit.complex.core.simd.exe  )
