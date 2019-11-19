#pragma once

#include <memory>

#ifdef GLASS_EXPORT
	#define GLASS_API __declspec(dllexport)
#else
	#define GLASS_API __declspec(dllimport)
#endif

#pragma region SHADER_ATTRIBUTES
	#define POSITIONS_ATTRIB 0x0
	#define TEXCOORDS_ATTRIB 0x1
#pragma endregion

#pragma region OPENGL
	#define MAX_TEXTURE_UNITS 32
#pragma endregion

#pragma region IOSTREAMING
	#define GET_LINE(stream, line) std::getline(stream, line)
#pragma endregion

#pragma region C++
	/*
		Param 1: Casted To
		Param 2: From
	*/
	#define SMART_CAST(CastTo, Obj)       std::dynamic_pointer_cast<CastTo>(Obj)

	/*
		Param 1: Casted To
		Param 2: From
	*/
	#define STATIC_CAST(CastTo, Obj)      static_cast<CastTo>(Obj)

	/*
		Param 1: Casted To
		Param 2: From
	*/
	#define REINTERPRET_CAST(CastTo, Obj) reinterpret_cast<CastTo>(Obj)

	/*
		Param 1: Casted To
		Param 2: From
	*/
	#define CONST_CAST(CastTo, Obj)       const_cast<CastTo>(Obj)
#pragma endregion

namespace Glass
{
	template<typename T>
	using UniqueScope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr UniqueScope<T> CreateUniqueScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward(Args)(args)...);
	}

	template<typename T>
	using SharedScope = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr SharedScope<T> CreateSharedScope(Args&& ... args)
	{
		return std::make_shared<T>(std::forward(Args)(args)...);
	}
}
