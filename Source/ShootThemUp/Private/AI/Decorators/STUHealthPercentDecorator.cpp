// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUHealthPercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
