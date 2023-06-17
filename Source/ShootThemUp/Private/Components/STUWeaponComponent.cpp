// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)

	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
 }

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{

		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}

}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);

}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex) {

	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);

	}

	CurrentWeapon = Weapons[WeaponIndex];
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {//
		return Data.WeaponClass == CurrentWeapon->GetClass(); //
		});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage); 
}


void USTUWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);

}

void USTUWeaponComponent::InitAnimations()
{

	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}
	

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify) 
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
	}
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

		EquipAnimInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

	ReloadAnimInProgress = false;
}


bool USTUWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;

}

bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
	return CurrentWeapon//
		&& !EquipAnimInProgress//
		&& !ReloadAnimInProgress//
		&& CurrentWeapon->CanReload();

}

void USTUWeaponComponent::Reload()
{
	ChangeClip();
}

void USTUWeaponComponent::OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon) return;
	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();

	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}

void USTUWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}
bool USTUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}


bool USTUWeaponComponent::NeedAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}