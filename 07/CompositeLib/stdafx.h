// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#include <gsl/gsl>

#include <algorithm>
#include <cstdint>
#include <intsafe.h>
#include <memory>
#include <vector>

#include <boost/limits.hpp>
#include <boost/optional/optional.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/any_range.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/numeric.hpp>
