// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include <array>
#include <string>
#include <stdint.h>
#include <functional>

#pragma warning (push, 3)

// github.com/miloyip/rapidjson // Ask Shambir: use it or my couch-bicycle class?
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Network.hpp>

#pragma warning (pop)