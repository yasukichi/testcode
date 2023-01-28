// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "RenderTestStyle.h"

class FRenderTestCommands : public TCommands<FRenderTestCommands>
{
public:

	FRenderTestCommands()
		: TCommands<FRenderTestCommands>(TEXT("RenderTest"), NSLOCTEXT("Contexts", "RenderTest", "RenderTest Plugin"), NAME_None, FRenderTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};