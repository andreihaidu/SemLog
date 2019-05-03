// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "USemLogOwl.h"

// Define logging types
DEFINE_LOG_CATEGORY(LogSLOwl);

#define LOCTEXT_NAMESPACE "FUSemLogOwl"

void FUSemLogOwl::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUSemLogOwl::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUSemLogOwl, USemLogOwl)