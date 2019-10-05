#pragma once

#ifdef GLASS_EXPORT
	#define GLASS_API __declspec(dllexport)
#else
	#define GLASS_API __declspec(dllimport)
#endif