#pragma once

#include "Core/PlatformDetection.h"

#ifdef SFN_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <array>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Core/Base.h"

#include "Core/Log.h"

#include "Debug/Instrumentor.h"

#ifdef SFN_PLATFORM_WINDOWS
#include <Windows.h>
#endif
