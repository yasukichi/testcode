#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"

class FSimpleShader : public FGlobalShader
{
public:
	FSimpleShader() {}

	FSimpleShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer) {}

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

class FSimpleShaderVS : public FSimpleShader
{
	DECLARE_SHADER_TYPE(FSimpleShaderVS, Global);
public:
	FSimpleShaderVS() {}

	FSimpleShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FSimpleShader(Initializer)
	{
	}
};

class FSimpleShaderPS : public FSimpleShader
{
	DECLARE_SHADER_TYPE(FSimpleShaderPS, Global);
public:
	FSimpleShaderPS() {}

	FSimpleShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FSimpleShader(Initializer)
	{
	}
};

class SIMPLERENDERER_API FSimpleRenderer
{
public:
	FSimpleRenderer() {};

	void Render(class UTextureRenderTarget2D* RenderTarget);
};
