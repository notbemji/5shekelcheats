#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual( void *name, int offset ) {
		int *table = *( int ** ) name;
		int address = table[ offset ];
		return ( t ) ( address );
	}
	template <typename T, typename ... args_t>
	inline constexpr T call_vfunc(void* thisptr, std::size_t nIndex, args_t... argList)
	{
		using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
		return (*(VirtualFn**)thisptr)[nIndex](thisptr, argList...);
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;

	void reveal_competitive_ranks();
}
