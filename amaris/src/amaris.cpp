#include "amaris.h"
#include "console.h"

#include <iostream>

namespace amaris
{
	void sayHello()
	{
		Console cns(ConsoleColor::YELLOW);
		cns.print("Let's join Amaris!");
	}
}