#pragma once

#include "Coreminimal.h"
#include "UnrealClient.h"

class FRenderTestViewportClient : public FViewportClient
{
	UTextureRenderTarget2D *RenderTarget;
public:
	FRenderTestViewportClient();
	virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;
};