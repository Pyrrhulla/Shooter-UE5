// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"

int32 USTUGameDataWidget::GetKillsNum() const 
{
	const auto PlayerState = GetSTUPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0; 
}
int32 USTUGameDataWidget::GetTotalRoundsNum() const 
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNums : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const 
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}


ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const 
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const 
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;

}
