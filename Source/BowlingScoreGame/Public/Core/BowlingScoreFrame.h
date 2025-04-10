// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BowlingScoreFrame.generated.h"

/**
 * 
 */

UENUM()
enum class EFrameTypeScore:uint8
{
	Normal,
	Spare,
	Strike
};

UCLASS()
class BOWLINGSCOREGAME_API UBowlingScoreFrame : public UObject
{
public:
	GENERATED_BODY()
	
	TArray<int32> RoundScores;
	
	UBowlingScoreFrame();
	
	virtual EFrameTypeScore ValidateFrame();

	virtual int AddRoundsScores();
};
