//Copyright (c) 2024 Alexander Goncharov. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FMultiLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
