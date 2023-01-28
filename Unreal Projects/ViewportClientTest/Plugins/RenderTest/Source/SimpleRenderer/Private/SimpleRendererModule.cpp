#include "SimpleRenderer.h"
#include "ShaderCore.h"
#include "Interfaces/IPluginManager.h"

void FSimpleRendererModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("RenderTest"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/RenderTest"), PluginShaderDir);
}

void FSimpleRendererModule::ShutdownModule()
{
}

IMPLEMENT_MODULE(FSimpleRendererModule, SimpleRenderer)