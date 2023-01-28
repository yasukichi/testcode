#include "SimpleShader.h"

IMPLEMENT_SHADER_TYPE(, FSimpleShaderVS, TEXT("/Plugin/RenderTest/SimpleShader.usf"), TEXT("MainVS"), SF_Vertex)
IMPLEMENT_SHADER_TYPE(, FSimpleShaderPS, TEXT("/Plugin/RenderTest/SimpleShader.usf"), TEXT("MainPS"), SF_Pixel)

#include "Containers/DynamicRHIResourceArray.h"

struct FColorVertex {
	FVector2D Position;
	FVector4 Color;
};

class FSimpleVertexBuffer : public FVertexBuffer
{
public:
	void InitRHI() override
	{
		TResourceArray<FColorVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
		Vertices.SetNumUninitialized(3);

		Vertices[0].Position = FVector2D(0, 0.75);
		Vertices[0].Color = FVector4(1, 0, 0, 1);

		Vertices[1].Position = FVector2D(0.75, -0.75);
		Vertices[1].Color = FVector4(0, 1, 0, 1);

		Vertices[2].Position = FVector2D(-0.75, -0.75);
		Vertices[2].Color = FVector4(0, 0, 1, 1);

		FRHIResourceCreateInfo CreateInfo(&Vertices);
		VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};

TGlobalResource<FSimpleVertexBuffer> GSimpleVertexBuffer;

class FColorVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;
	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;
		uint32 Stride = sizeof(FColorVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FColorVertex, Position), VET_Float2, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FColorVertex, Color), VET_Float4, 1, Stride));
		VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
	}
	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

TGlobalResource<FColorVertexDeclaration> GSimpleVertexDeclaration;

class FSimpleIndexBuffer : public FIndexBuffer
{
public:
	void InitRHI() override
	{
		const uint16 Indices[] = { 0, 1, 2 };

		TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;
		uint32 NumIndices = ARRAY_COUNT(Indices);
		IndexBuffer.AddUninitialized(NumIndices);
		FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));

		FRHIResourceCreateInfo CreateInfo(&IndexBuffer);
		IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};

TGlobalResource<FSimpleIndexBuffer> GSimpleIndexBuffer;

#include "RHIStaticStates.h"

static void DrawTestShaderRenderTarget_RenderThread(
	FRHICommandListImmediate& RHICmdList,
	FTextureRenderTargetResource* OutputRenderTargetResource
)
{
	check(IsInRenderingThread());

	FRHIRenderPassInfo RPInfo(OutputRenderTargetResource->GetRenderTargetTexture(), ERenderTargetActions::DontLoad_Store, OutputRenderTargetResource->TextureRHI);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("SimpleRendererShaderPass"));
	{
		// Get shaders.
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
		TShaderMapRef<FSimpleShaderVS> VertexShader(GlobalShaderMap);
		TShaderMapRef<FSimpleShaderPS> PixelShader(GlobalShaderMap);

		// Set the graphic pipeline state.
		FGraphicsPipelineStateInitializer GraphicsPSOInit;
		RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
		GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
		GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
		GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
		GraphicsPSOInit.PrimitiveType = PT_TriangleList;
		GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GSimpleVertexDeclaration.VertexDeclarationRHI;
		GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
		GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
		SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

		// Update viewport.
		RHICmdList.SetViewport(
			0, 0, 0.f,
			OutputRenderTargetResource->GetSizeX(), OutputRenderTargetResource->GetSizeY(), 1.f);

		// Set the vertextBuffer.
		RHICmdList.SetStreamSource(0, GSimpleVertexBuffer.VertexBufferRHI, 0);

		RHICmdList.DrawIndexedPrimitive(
			GSimpleIndexBuffer.IndexBufferRHI,
			/*BaseVertexIndex=*/ 0,
			/*MinIndex=*/ 0,
			/*NumVertices=*/ 3,
			/*StartIndex=*/ 0,
			/*NumPrimitives=*/ 1,
			/*NumInstances=*/ 1);
	}
	RHICmdList.EndRenderPass();
}

#include "TextureResource.h"
#include "Engine/TextureRenderTarget2D.h"

void FSimpleRenderer::Render(UTextureRenderTarget2D* RenderTarget)
{
	check(IsInGameThread());

	if (!RenderTarget)
	{
		return;
	}

	FTextureRenderTargetResource* TextureRenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
	ENQUEUE_RENDER_COMMAND(CaptureCommand)(
		[TextureRenderTargetResource](FRHICommandListImmediate& RHICmdList)
		{
			DrawTestShaderRenderTarget_RenderThread(RHICmdList, TextureRenderTargetResource);
		}
	);
}

