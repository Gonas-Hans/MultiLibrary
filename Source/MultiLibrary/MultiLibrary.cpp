//Copyright (c) 2024 Alexander Goncharov. All Rights Reserved.

#include "MultiLibrary.h"

#define LOCTEXT_NAMESPACE "FMultiLibraryModule"

void FMultiLibraryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IModuleInterface::StartupModule();
}

void FMultiLibraryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMultiLibraryModule, MultiLibrary)