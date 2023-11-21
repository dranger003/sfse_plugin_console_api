#include "pch.h"

extern "C"
{
	PLUGIN_API SFSEPluginVersionData SFSEPlugin_Version = {
		SFSEPluginVersionData::kVersion,
		2,
		PLUGIN_NAME,
		PLUGIN_AUTHOR,
		SFSEPluginVersionData::kAddressIndependence_Signatures,
		SFSEPluginVersionData::kStructureIndependence_NoStructs,
		PLUGIN_COMPATIBLE_VERSIONS,
		0,
		0,
		0,
	};

	PLUGIN_API bool SFSEPlugin_Preload(const SFSEInterface* sfse) {
		return plugin::app::inst()->preload(sfse);
	}

	PLUGIN_API bool SFSEPlugin_Load(const SFSEInterface* sfse) {
		return plugin::app::inst()->load(sfse);
	}
}
