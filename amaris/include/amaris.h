#pragma once

#ifdef _WIN32
#ifdef AMARIS_EXPORT
#define AMARIS_API __declspec(dllexport)
#else
#define AMARIS_API __declspec(dllimport)
#endif
#else
#define AMARIS_API __attribute__ ((visibility ("default")))
#endif

namespace amaris
{
	AMARIS_API void sayHello();
}