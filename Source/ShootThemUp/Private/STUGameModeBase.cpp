// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"
#include "STUBaseCharacter.h"
#include "STUPlayerController.h"
#include "UI/STUGameHUD.h"

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUGameModeBase::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();

}


