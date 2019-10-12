#pragma once

#include <memory>

#ifdef GLASS_EXPORT
	#define GLASS_API __declspec(dllexport)
#else
	#define GLASS_API __declspec(dllimport)
#endif

#pragma region IOSTREAMING

	#define GET_LINE(stream, line) std::getline(stream, line)

#pragma endregion

#pragma region GLS_RENDERING

	#define gls_GEN_VERTEX_ARRAY(size, buffer) glGenVertexArrays(size, &buffer)
	#define gls_GEN_BUFFER(size, buffer) glGenBuffers(size, &buffer)
	#define gls_BIND_VERTEX_ARRAY(buffer) glBindVertexArray(buffer)

	#define gls_BIND_BUFFER(target, buffer) glBindBuffer(target, buffer)

	#define gls_STORE_BUFFER_DATA(target, buffer, allocation_size, data) gls_BIND_BUFFER(target, buffer); \
																		 glBufferData(target, allocation_size, data, GL_STATIC_DRAW)

	#define gls_SET_SHADER_ATTRIB(index, attribute_size, stride, voidparam) glVertexAttribPointer(index, attribute_size, GL_FLOAT, GL_FALSE, stride, voidparam) 
	#define gls_ENABLE_SHADED_ATTRIB_INDEX(index) glEnableVertexAttribArray(index)

	#define DRAW_ELEMENTS(mode, num_indices) glDrawElements(mode, num_indices, GL_UNSIGNED_INT, 0)

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
