#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include "export.h"
#include <string>

namespace Utils {

	static void DebugMessage(std::string mssg)
	{
		std::cout << mssg << std::endl;
	}

}


#endif // !UTILS_H

