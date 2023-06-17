// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public: 
	UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

};
