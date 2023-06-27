// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All)

void ASTUPlayerState::LogInfo()

{
	UE_LOG(LogSTUPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);

}

