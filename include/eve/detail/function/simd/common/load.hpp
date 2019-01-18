//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Emulation
  template<typename Pack, typename Pointer>
  EVE_FORCEINLINE Pack load(as_<Pack> const&, eve::emulated_ const&, Pointer ptr) noexcept
  {
    auto impl = [&](auto... I)
                {
                  auto deref = [&](auto p, auto const& i) { std::advance(p,i); return *p; };
                  return Pack(deref(ptr,static_cast<std::ptrdiff_t>(I))...);
                };

    return apply<Pack::size()>(impl);
  }

  template<typename T, typename Pack, std::size_t N>
  EVE_FORCEINLINE Pack load ( as_<Pack> const& tgt, eve::emulated_ const& mode
                            , aligned_ptr<T,N> ptr
                            ) noexcept
  {
    return load(tgt,mode,ptr.get());
  }

  template<typename Iterator, typename ABI, typename Pack>
  EVE_FORCEINLINE Pack load(as_<Pack> const& tgt, ABI const&, Iterator b, Iterator) noexcept
  {
    return load(tgt,eve::emulated_{}, b);
  }

  //------------------------------------------------------------------------------------------------
  // Aggregation
  template<typename Pack, typename Pointer>
  EVE_FORCEINLINE Pack load(as_<Pack> const& tgt, eve::aggregated_ const&, Pointer ptr) noexcept
  {
    using storage_t = typename Pack::storage_type;
    using subpack_t = typename storage_t::value_type;

    return Pack(storage_t{ subpack_t(ptr), subpack_t(ptr + subpack_t::size())});
  }

  template<typename T, typename Pack, std::size_t N>
  EVE_FORCEINLINE Pack load ( as_<Pack> const& tgt, eve::aggregated_ const& mode
                            , aligned_ptr<T,N> ptr
                            ) noexcept
  {
    using storage_t = typename Pack::storage_type;
    using subpack_t = typename storage_t::value_type;
    return Pack(storage_t{ subpack_t(ptr), subpack_t(ptr + subpack_t::size())});
  }
}

#endif

