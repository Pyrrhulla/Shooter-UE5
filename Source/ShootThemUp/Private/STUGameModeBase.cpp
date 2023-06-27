// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"
#include "STUBaseCharacter.h"
#include "STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUGameModeBase::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUGameModeBase::StaticClass();
}

void ASTUGameModeBase::StartPlay() 
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIController);
	}
}

void ASTUGameModeBase::StartRound()
{ 
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}
void ASTUGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogSTUGameModeBase, Display, TEXT("Time: %i / Rounds: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNums);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNums)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogSTUGameModeBase, Display, TEXT("-------YOU DIED-----"));
			LogPlayerInfo();
		}

	}
}

void ASTUGameModeBase::ResetPlayers() 
{
	if(!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}
void ASTUGameModeBase::ResetOnePlayer(AController* Controller) 
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetPlayerColor(Controller);

}

void ASTUGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}
	FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
	{
		if (TeamID - 1 < GameData.TeamColors.Num())
		{
			return GameData.TeamColors[TeamID - 1];
		}
		return GameData.DefaultTeamColor;
	}
	void ASTUGameModeBase::SetPlayerColor(AController* Controller)
	{
		if (!Controller) return;
		const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
		if (!Character) return;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) return;

		Character->SetPlayerColor(PlayerState->GetTeamColor());
	}

	void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
	{ 
	
		const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
		const auto VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

		if (KillerPlayerState)
		{
			KillerPlayerState->AddKill();
		}

		if (VictimPlayerState)
		{
			VictimPlayerState->AddDeath();
		}
	
	}

void ASTUGameModeBase::LogPlayerInfo()
{
		
	if (!GetWorld()) return;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}
