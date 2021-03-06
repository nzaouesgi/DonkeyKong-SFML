// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/OpenGL.hpp>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "FLAC.lib")
#pragma comment(lib, "FLAC++.lib")
#pragma comment(lib, "ogg.lib")
#pragma comment(lib, "vorbis.lib")
#pragma comment(lib, "vorbisenc.lib")
#pragma comment(lib, "vorbisfile.lib")
#pragma comment(lib, "bz2.lib")
#pragma comment(lib, "zlib.lib")


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")

#endif //PCH_H
