/// \file
/// \brief Macros to create specialized trait templates.
///
/// \copyright
///   Copyright 2017 by Google Inc. All Rights Reserved.
///
/// \copyright
///   Licensed under the Apache License, Version 2.0 (the "License"); you may
///   not use this file except in compliance with the License. You may obtain a
///   copy of the License at
///
/// \copyright
///   http://www.apache.org/licenses/LICENSE-2.0
///
/// \copyright
///   Unless required by applicable law or agreed to in writing, software
///   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
///   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
///   License for the specific language governing permissions and limitations
///   under the License.

#ifndef INCLUDE_ASH_TRAITS_TRAIT_FACTORIES_H_
#define INCLUDE_ASH_TRAITS_TRAIT_FACTORIES_H_

#include <type_traits>
#include "ash/traits/type_traits.h"

namespace ash {

/// Trait classes for type introspection.
namespace traits {

/// \brief Define a checker template `struct` to verify whether a class has a
/// non-`const` method with the given name.
///
/// Specific return and argument types are provided to the `struct` at template
/// instantiation. As there's no way to provide a name at template instantiation
/// type, a new instantiation of this macro is required for every distinct name
/// to check.
///
/// \param CHECKER_NAME Name of the generated template `struct`.
/// \param METHOD Name of the (non-`const`) method to check for.
#define ASH_MAKE_METHOD_CHECKER(CHECKER_NAME, METHOD)                         \
  template <typename, typename T>                                             \
  struct CHECKER_NAME {                                                       \
    static_assert(std::integral_constant<T, false>::value,                    \
                  "Second template parameter needs to be of function type."); \
  };                                                                          \
  template <typename C, typename Ret, typename... Args>                       \
  struct CHECKER_NAME<C, Ret(Args...)> {                                      \
   private:                                                                   \
    template <typename T>                                                     \
    static constexpr auto check(T*) -> typename std::is_same<                 \
        decltype(std::declval<T>().METHOD(std::declval<Args>()...)),          \
        Ret>::type;                                                           \
    template <typename>                                                       \
    static constexpr std::false_type check(...);                              \
    typedef decltype(check<C>(0)) type;                                       \
                                                                              \
   public:                                                                    \
    static constexpr bool value = type::value;                                \
  };

/// \brief Define a checker template `struct` to verify whether a class has a
/// `const` method with the given name.
///
/// Specific return and argument types are provided to the `struct` at template
/// instantiation. As there's no way to provide a name at template instantiation
/// type, a new instantiation of this macro is required for every distinct name
/// to check.
///
/// \param CHECKER_NAME Name of the generated template `struct`.
/// \param METHOD Name of the (`const`) method to check for.
#define ASH_MAKE_CONST_METHOD_CHECKER(CHECKER_NAME, METHOD)                   \
  template <typename, typename T>                                             \
  struct CHECKER_NAME {                                                       \
    static_assert(std::integral_constant<T, false>::value,                    \
                  "Second template parameter needs to be of function type."); \
  };                                                                          \
  template <typename C, typename Ret, typename... Args>                       \
  struct CHECKER_NAME<C, Ret(Args...)> {                                      \
   private:                                                                   \
    template <typename T>                                                     \
    static constexpr auto check(T*) -> typename std::is_same<                 \
        decltype(std::declval<const T>().METHOD(std::declval<Args>()...)),    \
        Ret>::type;                                                           \
    template <typename>                                                       \
    static constexpr std::false_type check(...);                              \
    typedef decltype(check<C>(0)) type;                                       \
                                                                              \
   public:                                                                    \
    static constexpr bool value = type::value;                                \
  };

/// \brief Define a checker template `struct` to verify whether a class has a
/// nested type with a given name.
///
/// As there's no way to provide a name at template instantiation type, a new
/// instantiation of this macro is required for every distinct name to check.
///
/// \param CHECKER_NAME Name of the generated template `struct`.
/// \param TYPE_NAME Name of the nested type to check for.
#define ASH_MAKE_NESTED_TYPE_CHECKER(CHECKER_NAME, TYPE_NAME)                 \
  template <typename T, typename Enable = void>                               \
  struct CHECKER_NAME : public std::false_type {};                            \
  template <typename T>                                                       \
  struct CHECKER_NAME<                                                        \
      T, typename ::ash::traits::enable_if_type<typename T::TYPE_NAME>::type> \
      : public std::true_type {};

/// \brief Define a checker template `struct` to verify whether a class has a
/// nested compile-time constant with a given name of a given type.
///
/// As there's no way to provide a name at template instantiation type, a new
/// instantiation of this macro is required for every distinct name to check.
///
/// \param CHECKER_NAME Name of the generated template `struct`.
/// \param CONSTANT_NAME Name of the nested constant to check for.
#define ASH_MAKE_NESTED_CONSTANT_CHECKER(CHECKER_NAME, CONSTANT_NAME)          \
  template <typename T, typename VT, typename Enable = void>                   \
  struct CHECKER_NAME : public std::false_type {};                             \
  template <typename T, typename VT>                                           \
  struct CHECKER_NAME<T, VT,                                                   \
                      typename std::enable_if<std::is_same<                    \
                          const VT, decltype(T::CONSTANT_NAME)>::value>::type> \
      : public std::true_type {};

}  // namespace traits

}  // namespace ash

#endif  // INCLUDE_ASH_TRAITS_TRAIT_FACTORIES_H_