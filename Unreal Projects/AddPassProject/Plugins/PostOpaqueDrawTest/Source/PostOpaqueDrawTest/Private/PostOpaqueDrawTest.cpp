// Copyright Epic Games, Inc. All Rights Reserved.

#include "PostOpaqueDrawTest.h"
#include "Interfaces/IPluginManager.h"
#include "TestRenderer.h"

#define LOCTEXT_NAMESPACE "FPostOpaqueDrawTestModule"

// 描画クラスオブジェクト
static ATestRenderer* TestRenderer = nullptr;

// 描画登録コマンド
static FAutoConsoleCommand CCmdPostOpaqueDrawTestRegister(TEXT("PostOpaqueDrawTest.Register"), TEXT(""),
	FConsoleCommandDelegate::CreateLambda([]()
		{
			FPostOpaqueDrawTestModule::RegisterDrawTest();
		}
));

// 描画解除コマンド
static FAutoConsoleCommand CCmdPostOpaqueDrawTestUnRegister(TEXT("PostOpaqueDrawTest.UnRegister"), TEXT(""),
	FConsoleCommandDelegate::CreateLambda([]()
		{
			FPostOpaqueDrawTestModule::UnRegisterDrawTest();
		}
));

void FPostOpaqueDrawTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// Shader Codeのフォルダをエンジンに登録
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("PostOpaqueDrawTest"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/PostOpaqueDrawTest"), PluginShaderDir);

	// 描画クラスオブジェクトを作成
	TestRenderer = new ATestRenderer();
}

void FPostOpaqueDrawTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
 	delete TestRenderer;
}

void FPostOpaqueDrawTestModule::RegisterDrawTest()
{
	// テスト描画クラスをエンジンに登録
	TestRenderer->Register();
}

void FPostOpaqueDrawTestModule::UnRegisterDrawTest()
{
	// テスト描画クラスを解除
	TestRenderer->UnRegister();
}
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPostOpaqueDrawTestModule, PostOpaqueDrawTest)