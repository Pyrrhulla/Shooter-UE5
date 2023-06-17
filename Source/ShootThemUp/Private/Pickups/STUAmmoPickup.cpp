// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUAmmoPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"


bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent-> TryToAddAmmo(WeaponType, ClipsAmount);
}