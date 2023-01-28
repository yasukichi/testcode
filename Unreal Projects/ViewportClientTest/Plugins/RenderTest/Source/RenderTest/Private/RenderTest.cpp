// Copyright Epic Games, Inc. All Rights Reserved.

#include "RenderTest.h"
#include "RenderTestStyle.h"
#include "RenderTestCommands.h"
#include "RenderTestViewportClient.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "Widgets/SViewport.h"
#include "Slate/SceneViewport.h"

static const FName RenderTestTabName("RenderTest");

#define LOCTEXT_NAMESPACE "FRenderTestModule"

void FRenderTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FRenderTestStyle::Initialize();
	FRenderTestStyle::ReloadTextures();

	FRenderTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FRenderTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FRenderTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FRenderTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(RenderTestTabName, FOnSpawnTab::CreateRaw(this, &FRenderTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FRenderTestTabTitle", "RenderTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FRenderTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FRenderTestStyle::Shutdown();

	FRenderTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RenderTestTabName);
}

TSharedRef<SDockTab> FRenderTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> Tab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ViewportWidget, SViewport)
			]
		];

	ViewportClient = MakeShareable(new FRenderTestViewportClient());
	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), ViewportWidget));
	ViewportWidget->SetViewportInterface(Viewport.ToSharedRef());

	return Tab;
}

void FRenderTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(RenderTestTabName);
}

void FRenderTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FRenderTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FRenderTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRenderTestModule, RenderTest)