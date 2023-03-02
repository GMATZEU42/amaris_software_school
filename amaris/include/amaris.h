#pragma once

#ifdef _WIN32
#define AMARIS_API __declspec(dllexport)
#else
// ToDo: insert linux export
#endif

namespace amaris
{
	AMARIS_API void sayHello();
}