#include "RenderTestViewportClient.h"
#include "SimpleRenderer/Public/SimpleShader.h"

#include "Runtime/Engine/Public/CanvasTypes.h"
#include "Runtime/Engine/Public/CanvasItem.h"
#include "Engine/TextureRenderTarget2D.h"

FRenderTestViewportClient::FRenderTestViewportClient()
{
	RenderTarget = NewObject<UTextureRenderTarget2D>(GetTransientPackage(), NAME_None, RF_Transient);
	RenderTarget->RenderTargetFormat = RTF_RGBA8;
	RenderTarget->InitAutoFormat(1024, 1024);
	RenderTarget->ClearColor = FLinearColor::Blue;
	RenderTarget->UpdateResource();
}

void FRenderTestViewportClient::Draw(FViewport* Viewport, FCanvas* Canvas)
{
	Canvas->Clear(FLinearColor::Black);
	if (RenderTarget)
	{
		FSimpleRenderer renderer;
		renderer.Render(RenderTarget);

		FCanvasTileItem Tile(FVector2D::ZeroVector, RenderTarget->Resource, Viewport->GetSizeXY(), FLinearColor(1, 1, 1, 1));
		Canvas->DrawItem(Tile);
	}
}