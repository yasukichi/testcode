// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class POSTOPAQUEDRAWTEST_API ATestRenderer
{
public:
    ATestRenderer();
    ~ATestRenderer();

    void Register();
    void UnRegister();

    void Renderer(FPostOpaqueRenderParameters& Parameters);

private:
    FDelegateHandle RendererDelegateHandle; // •`‰ædelegate‚Ìƒnƒ“ƒhƒ‹
};