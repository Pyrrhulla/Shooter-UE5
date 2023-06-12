// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUCharacterMovementComponent.h"
#include "STUBaseCharacter.h"


float USTUCharacterMovementComponent::GetMaxSpeed() const 
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
	return Player && Player-> IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}

