// Copyright Test Company, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BowlingScoreGameGameModeBase.generated.h"


UCLASS()
class BOWLINGSCOREGAME_API ABowlingScoreGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

	
};
