// Copyright Epic Games, Inc. All Rights Reserved.

#include "PostOpaqueDrawTestBPLibrary.h"
#include "PostOpaqueDrawTest.h"

UPostOpaqueDrawTestBPLibrary::UPostOpaqueDrawTestBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UPostOpaqueDrawTestBPLibrary::PostOpaqueDrawTestSampleFunction(float Param)
{
	return -1;
}

