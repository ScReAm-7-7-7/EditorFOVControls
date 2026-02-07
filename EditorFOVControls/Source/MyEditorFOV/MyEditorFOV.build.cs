using UnrealBuildTool;

public class MyEditorFOV : ModuleRules
{
    public MyEditorFOV(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "LevelEditor"
            });

            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "Slate",
                "SlateCore",
                "EditorFramework",
                "InputCore"
            });
        }
    }
}