// Copyright Test Company, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BowlingScoreFrame.h"
#include "BowlingScoreFinalFrame.generated.h"


UCLASS()
class BOWLINGSCOREGAME_API UBowlingScoreFinalFrame : public UBowlingScoreFrame
{
public:
	GENERATED_BODY()
	UBowlingScoreFinalFrame();
	virtual EFrameTypeScore ValidateFrame() override;
	virtual int AddRoundsScores() override;

};
