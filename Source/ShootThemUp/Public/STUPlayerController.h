// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	ASTUPlayerController();
	
protected: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTURespawnComponent* RespawnComponent;

};
