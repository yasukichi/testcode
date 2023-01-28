// Fill out your copyright notice in the Description page of Project Settings.

#include "TestRenderer.h"
#include "EngineModule.h"
#include "SceneRendering.h"
#include "PostProcess/SceneFilterRendering.h"
#include "PostProcess/PostProcessing.h"

ATestRenderer::ATestRenderer()
{
}

ATestRenderer::~ATestRenderer()
{
}

// レンダーモジュールに登録 
void ATestRenderer::Register()
{
	RendererDelegateHandle = GetRendererModule().RegisterPostOpaqueRenderDelegate(FPostOpaqueRenderDelegate::CreateRaw(this, &ATestRenderer::Renderer));
}

// レンダーモジュールから解除
void ATestRenderer::UnRegister()
{
	if (RendererDelegateHandle.IsValid())
	{
		GetRendererModule().RemovePostOpaqueRenderDelegate(RendererDelegateHandle);
		RendererDelegateHandle.Reset();
	}
}

//ピクセルシェーダーの定義
class FTestRendererPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FTestRendererPS);
	SHADER_USE_PARAMETER_STRUCT(FTestRendererPS, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_REF(FSceneTextureUniformParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

IMPLEMENT_SHADER_TYPE(, FTestRendererPS, TEXT("/Plugin/PostOpaqueDrawTest/Private/TestRenderer.usf"), TEXT("TestPS"), SF_Pixel);

// 実際の描画処理 
void ATestRenderer::Renderer(FPostOpaqueRenderParameters& Parameters)
{
	FRHICommandListImmediate& RHICmdList = *Parameters.RHICmdList;

	FTestRendererPS::FParameters PassParameters;
	TUniformBufferRef<FViewUniformShaderParameters> Ref;
	*Ref.GetInitReference() = Parameters.ViewUniformBuffer;
	PassParameters.View = Ref;
	PassParameters.SceneTextures = CreateSceneTextureUniformBuffer(RHICmdList, GMaxRHIFeatureLevel, ESceneTextureSetupMode::All);

	FUniformBufferStaticBindings GlobalUniformBuffers(PassParameters.SceneTextures);
	SCOPED_UNIFORM_BUFFER_GLOBAL_BINDINGS(RHICmdList, GlobalUniformBuffers);

	// 描画先をSceneColorに設定
	FRHIRenderPassInfo RPInfo(FSceneRenderTargets::Get(RHICmdList).GetSceneColor()->GetTargetableRHI(), ERenderTargetActions::Load_Store);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("PostOpaqueDrawTest"));
	RHICmdList.SetViewport(0, 0, 0.0f, Parameters.ViewportRect.Width(), Parameters.ViewportRect.Height(), 1.0f);

	TShaderMapRef<FPostProcessVS> VertexShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	TShaderMapRef<FTestRendererPS> PixelShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	// 半透明描画用のBlendStateの設定
	GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_Zero, BF_InverseSourceAlpha>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();

	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), PassParameters);

	// 実際の描画、View全体に描画する。
	DrawRectangle(
		RHICmdList,
		0, 0,
		Parameters.ViewportRect.Width(), Parameters.ViewportRect.Height(),
		0, 0,
		Parameters.ViewportRect.Width(), Parameters.ViewportRect.Height(),
		FIntPoint(Parameters.ViewportRect.Width(), Parameters.ViewportRect.Height()),
		FSceneRenderTargets::Get(RHICmdList).GetBufferSizeXY(),
		VertexShader);

	RHICmdList.EndRenderPass();
}
