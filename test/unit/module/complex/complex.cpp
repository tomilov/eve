//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <eve/complex/complex.hpp>
#include <eve/wide.hpp>

//==================================================================================================
// eve::complex<T> type specifications
//==================================================================================================
TTS_CASE_TPL("Check eve::complex<T> type specifications", float, double)
<typename T>(::tts::type<T>)
{
  TTS_EXPECT    ( eve::value                < eve::complex<T> > );
  TTS_EXPECT    ( eve::scalar_value         < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::simd_value           < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::real_value           < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::real_scalar_value    < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::real_simd_value      < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::floating_value       < eve::complex<T> > );
  TTS_EXPECT_NOT( eve::floating_scalar_value< eve::complex<T> > );
  TTS_EXPECT_NOT( eve::floating_simd_value  < eve::complex<T> > );

  TTS_EXPECT    ( eve::value                < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::scalar_value         < eve::wide< eve::complex<T> > > );
  TTS_EXPECT    ( eve::simd_value           < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::real_value           < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::real_scalar_value    < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::real_simd_value      < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::floating_value       < eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::floating_scalar_value< eve::wide< eve::complex<T> > > );
  TTS_EXPECT_NOT( eve::floating_simd_value  < eve::wide< eve::complex<T> > > );
};

//==================================================================================================
// eve::complex<T> constructor
//==================================================================================================
TTS_CASE_TPL("Check eve::complex<T> default constructors", float, double)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS( eve::complex<T>{}, eve::complex<T> );
  TTS_EXPR_IS( eve::wide<eve::complex<T>>{}, eve::wide<eve::complex<T>> );
};
