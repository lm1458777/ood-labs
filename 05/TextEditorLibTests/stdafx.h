// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#include <doctest/doctest.h> // must be included before <sstream>

#include <deque>
#include <memory>
#include <sstream>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
