// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "cpp_quick_start/cpp_quick_startGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodecpp_quick_startGameModeBase() {}
// Cross Module References
	CPP_QUICK_START_API UClass* Z_Construct_UClass_Acpp_quick_startGameModeBase_NoRegister();
	CPP_QUICK_START_API UClass* Z_Construct_UClass_Acpp_quick_startGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_cpp_quick_start();
// End Cross Module References
	void Acpp_quick_startGameModeBase::StaticRegisterNativesAcpp_quick_startGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_Acpp_quick_startGameModeBase_NoRegister()
	{
		return Acpp_quick_startGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_cpp_quick_start,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "cpp_quick_startGameModeBase.h" },
		{ "ModuleRelativePath", "cpp_quick_startGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Acpp_quick_startGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::ClassParams = {
		&Acpp_quick_startGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_Acpp_quick_startGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_Acpp_quick_startGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(Acpp_quick_startGameModeBase, 2736801099);
	template<> CPP_QUICK_START_API UClass* StaticClass<Acpp_quick_startGameModeBase>()
	{
		return Acpp_quick_startGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_Acpp_quick_startGameModeBase(Z_Construct_UClass_Acpp_quick_startGameModeBase, &Acpp_quick_startGameModeBase::StaticClass, TEXT("/Script/cpp_quick_start"), TEXT("Acpp_quick_startGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(Acpp_quick_startGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
