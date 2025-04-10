// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Core/BowlingScoreModel.h"
#include "BowlingScoreGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BOWLINGSCOREGAME_API ABowlingScoreGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

	
};
