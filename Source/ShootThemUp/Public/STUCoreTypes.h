#pragma once

#include "STUCoreTypes.generated.h"
//weapon
class ASTUBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossHairIcon;

};
//health
DECLARE_MULTICAST_DELEGATE(FOnDeath)
//DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float)

//vfx
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float FadeOutTime = 0.7f;


};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FDecalData DecalData;

};