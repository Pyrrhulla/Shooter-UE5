// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;
class USTURespawnComponent; 

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()
public: 
	ASTUAIController();

protected: 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USTURespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;

};
