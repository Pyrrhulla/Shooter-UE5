// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
