// Fill out your copyright notice in the Description page of Project Settings.

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
