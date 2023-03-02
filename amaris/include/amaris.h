#pragma once

#ifdef _WIN32
#define AMARIS_API __declspec(dllexport)
#else
#define AMARIS_API __attribute__ ((visibility ("default")))
#endif

namespace amaris
{
	AMARIS_API void sayHello();
}