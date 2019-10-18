// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN        // Exclude rarely-used stuff from Windows headers

// Third-party includes
#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Windows headers
#include <windows.h>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <vector>

#endif //PCH_H