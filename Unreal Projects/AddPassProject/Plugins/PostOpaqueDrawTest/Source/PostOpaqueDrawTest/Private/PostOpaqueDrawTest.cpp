// Copyright Epic Games, Inc. All Rights Reserved.

#include "PostOpaqueDrawTest.h"
#include "Interfaces/IPluginManager.h"
#include "TestRenderer.h"

#define LOCTEXT_NAMESPACE "FPostOpaqueDrawTestModule"

// �`��N���X�I�u�W�F�N�g
static ATestRenderer* TestRenderer = nullptr;

// �`��o�^�R�}���h
static FAutoConsoleCommand CCmdPostOpaqueDrawTestRegister(TEXT("PostOpaqueDrawTest.Register"), TEXT(""),
	FConsoleCommandDelegate::CreateLambda([]()
		{
			FPostOpaqueDrawTestModule::RegisterDrawTest();
		}
));

// �`������R�}���h
static FAutoConsoleCommand CCmdPostOpaqueDrawTestUnRegister(TEXT("PostOpaqueDrawTest.UnRegister"), TEXT(""),
	FConsoleCommandDelegate::CreateLambda([]()
		{
			FPostOpaqueDrawTestModule::UnRegisterDrawTest();
		}
));

void FPostOpaqueDrawTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// Shader Code�̃t�H���_���G���W���ɓo�^
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("PostOpaqueDrawTest"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/PostOpaqueDrawTest"), PluginShaderDir);

	// �`��N���X�I�u�W�F�N�g���쐬
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
	// �e�X�g�`��N���X���G���W���ɓo�^
	TestRenderer->Register();
}

void FPostOpaqueDrawTestModule::UnRegisterDrawTest()
{
	// �e�X�g�`��N���X������
	TestRenderer->UnRegister();
}
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPostOpaqueDrawTestModule, PostOpaqueDrawTest)