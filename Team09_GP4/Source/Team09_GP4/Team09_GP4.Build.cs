// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team09_GP4 : ModuleRules
{
	public Team09_GP4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks", "Niagara" });
	}
}
