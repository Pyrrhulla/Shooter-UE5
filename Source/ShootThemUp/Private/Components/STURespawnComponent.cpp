// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

// Sets default values for this component's properties
USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime; 
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));

	}
}