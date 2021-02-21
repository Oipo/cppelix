#pragma once

#include <ichor/ConstevalHash.h>
#include <ichor/stl/Any.h>
#include <ichor/stl/PolymorphicAllocator.h>
#include <string_view>
#include <unordered_map>

#if __cpp_lib_constexpr_string >= 201907L
#if __cpp_lib_constexpr_vector >= 201907L
#define ICHOR_CONSTEXPR constexpr
#else
#define ICHOR_CONSTEXPR
#endif
#else
#define ICHOR_CONSTEXPR
#endif

// GNU C Library contains defines in sys/sysmacros.h. However, for compatibility reasons, this header is included in sys/types.h. Which is used by std.
#undef major
#undef minor

namespace Ichor {
    template<typename...>
    struct typeList {};

    template<typename... Type>
    struct OptionalList_t: typeList<Type...>{};

    template<typename... Type>
    struct RequiredList_t: typeList<Type...>{};

    template<typename... Type>
    struct InterfacesList_t: typeList<Type...>{};

    template<typename... Type>
    inline constexpr OptionalList_t<Type...> OptionalList{};

    template<typename... Type>
    inline constexpr RequiredList_t<Type...> RequiredList{};

    template<typename... Type>
    inline constexpr InterfacesList_t<Type...> InterfacesList{};

#if __cpp_lib_generic_unordered_lookup >= 201811
    struct string_hash {
        using transparent_key_equal = std::equal_to<>;  // Pred to use
        using hash_type = std::hash<std::string_view>;  // just a helper local type
        size_t operator()(std::string_view txt) const   { return hash_type{}(txt); }
        size_t operator()(const std::string& txt) const { return hash_type{}(txt); }
        size_t operator()(const char* txt) const        { return hash_type{}(txt); }
    };

    using IchorProperties = std::pmr::unordered_map<std::pmr::string, Ichor::any, string_hash>;
#else
//    using IchorProperties = std::pmr::unordered_map<std::pmr::string, Ichor::any>;
    using IchorProperties = std::unordered_map<std::pmr::string, Ichor::any, std::hash<std::pmr::string>, std::equal_to<>, Ichor::PolymorphicAllocator<std::pair<const std::pmr::string, Ichor::any>>>;
#endif

    inline constexpr bool PreventOthersHandling = false;
    inline constexpr bool AllowOthersHandling = true;
}