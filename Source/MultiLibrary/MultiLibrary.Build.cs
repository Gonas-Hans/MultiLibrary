//Copyright (c) 2024 Alexander Goncharov. All Rights Reserved.

using UnrealBuildTool;

public class MultiLibrary : ModuleRules
{
	public MultiLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
				
		
		PrivateIncludePaths.AddRange(new string[] { });
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
			}
			);
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
		
	}
}
