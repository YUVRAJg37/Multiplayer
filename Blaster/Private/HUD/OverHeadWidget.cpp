// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverHeadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverHeadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	RemoveFromParent();
}

void UOverHeadWidget::SetDisplayText(FString TextToDisplay)
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverHeadWidget::ShowPlayerNetRole(APawn* Pawn)
{
	ENetRole RemoteRole = Pawn->GetLocalRole();
	FString Role;

	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority :
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_SimulatedProxy :
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_AutonomousProxy :
		Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_None :
		Role = FString("None");
		break;
		default:
			Role = FString("Default");
	}

	FString PlayerName;

	if(Pawn)
	{
		APlayerState* PlayerState = Pawn->GetPlayerState();
		if(PlayerState)
		{
			PlayerName =  PlayerState->GetPlayerName();
		}
	}
	
	FString RemoteRoleString = FString::Printf(TEXT("%s Remote Role : %s"), *PlayerName,  *Role);
	SetDisplayText(RemoteRoleString);
}
