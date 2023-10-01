#pragma once

#include "sfse/PluginAPI.h"

#include "sfse_common/sfse_version.h"
#include "sfse_common/BranchTrampoline.h"
#include "sfse_common/SafeWrite.h"
#include "sfse_common/Relocation.h"

#include "xbyak/xbyak/xbyak.h"

#pragma warning(disable: 4200)
#include "sfse/GameUI.h"
#include "sfse/GameReferences.h"
#pragma warning(default: 4200)

#ifdef _DEBUG
#pragma comment(lib, "../sfse/sfse/build/sfse_common/Debug/sfse_common.lib")
//#pragma comment(lib, "../sfse/sfse/build/Debug/sfse_1_7_33.lib")
#else
#pragma comment(lib, "../sfse/sfse/build/sfse_common/Release/sfse_common.lib")
//#pragma comment(lib, "../sfse/sfse/build/Release/sfse_1_7_33.lib")
#endif

#define PLUGIN_API						__declspec(dllexport)
#define PLUGIN_NAME						"sfse_plugin_console_api"
#define PLUGIN_AUTHOR					"stonegdi"
#define PLUGIN_COMPATIBLE_VERSIONS		{ RUNTIME_VERSION_1_7_33, 0 }
