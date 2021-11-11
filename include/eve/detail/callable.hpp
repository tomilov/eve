//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Tag> concept extensible_callable = requires(Tag)
  {
    typename Tag::eve_supports_extension;
  };

  template<typename Tag> concept maskable_callable = requires(Tag)
  {
    typename Tag::eve_supports_masking;
  };

  template<typename T, typename Dummy = void> struct callable_;
}

namespace eve::detail
{

  template<typename Tag> struct supports_extension
  {
    using eve_supports_extension = void;

    template<typename... Ts>
    EVE_FORCEINLINE auto operator()(Ts... args) const noexcept
    requires( tag_dispatchable<Tag,Ts...> )
    {
      return tagged_dispatch(Tag{}, args...);
    }
  };

  template<typename Condition, typename Tag> struct masked_callable;

  template<typename Tag> struct supports_masking
  {
    using eve_supports_masking = void;

    template<value Condition>
    EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept
    {
      auto cond = if_(to_logical(c));
      return masked_callable<decltype(cond), Tag>{cond};
    }

    template<conditional_expr Condition>
    EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept
    {
      return masked_callable<Condition, Tag>{c};
    }
  };
}
