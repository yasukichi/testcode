// Copyright Epic Games, Inc. All Rights Reserved.

#include "RenderTestCommands.h"

#define LOCTEXT_NAMESPACE "FRenderTestModule"

void FRenderTestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "RenderTest", "Bring up RenderTest window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
