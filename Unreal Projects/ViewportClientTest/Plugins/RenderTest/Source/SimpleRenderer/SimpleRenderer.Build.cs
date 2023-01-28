using UnrealBuildTool;

public class SimpleRenderer : ModuleRules
{
    public SimpleRenderer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
                {
            }
        );

        PrivateIncludePaths.AddRange(
            new string[]
                  {
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                        "Core",
                        "CoreUObject",
                         "Engine",
                        "RenderCore",
                        "Projects",
                        "RHI"
                  }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            }
        );
    }
}