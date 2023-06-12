// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;


	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	virtual bool Initialize() override; 

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void OnTakeDamage();

private:
	USTUWeaponComponent* GetWeaponComponent() const;

	void OnHealthChanged(float Health, float HealthDelta);
};
