// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class petitcon25 : ModuleRules
{
	public petitcon25(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"petitcon25",
			"petitcon25/Variant_Platforming",
			"petitcon25/Variant_Platforming/Animation",
			"petitcon25/Variant_Combat",
			"petitcon25/Variant_Combat/AI",
			"petitcon25/Variant_Combat/Animation",
			"petitcon25/Variant_Combat/Gameplay",
			"petitcon25/Variant_Combat/Interfaces",
			"petitcon25/Variant_Combat/UI",
			"petitcon25/Variant_SideScrolling",
			"petitcon25/Variant_SideScrolling/AI",
			"petitcon25/Variant_SideScrolling/Gameplay",
			"petitcon25/Variant_SideScrolling/Interfaces",
			"petitcon25/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
