// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

	void SetShotDirection(const FVector& Direction) {ShotDirection = Direction;}

protected:

	UPROPERTY(VisibleAnywhere, category = "Weapon")
		USphereComponent* CollisionComponent;


	UPROPERTY(VisibleAnywhere, category = "Weapon")
		UProjectileMovementComponent* MovementComponent_new;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
		USTUWeaponFXComponent* WeaponFXComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
		float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
		float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
		bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
		float LifeSeconds = 5.0f;

	virtual void BeginPlay() override;

private: 
	FVector ShotDirection; 
	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const; 
};
