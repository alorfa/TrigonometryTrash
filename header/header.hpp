#pragma once

#define H_DEBUG

#ifdef H_DEBUG

#include <iostream>

#define PRINT(x) std::cerr << #x " = " << (x) << std::endl
#define PRINTR(x) std::cerr << "\r" << #x " = " << (x) << "        "

#else

#define PRINT(x)
#define PRINTR(x)

#endif