// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NBC_UA_HW02 : ModuleRules
{
	public NBC_UA_HW02(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
