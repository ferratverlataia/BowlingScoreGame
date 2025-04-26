// Copyright Test Company, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BowlingScoreFrame.h"
#include "GameFramework/Actor.h"
#include "BowlingScoreModel.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFrameScoreChanged,int32,FrameScoreIndex,int32,FrameScoreValue,int32,MaxScoreValue);
UCLASS()
class BOWLINGSCOREGAME_API ABowlingScoreModel : public AActor
{
	GENERATED_BODY()

public:
	ABowlingScoreModel();
	virtual ~ABowlingScoreModel() override;
	//Our Array of Frames inside the game
	UPROPERTY()
	TArray<UBowlingScoreFrame*> BowlingFrames;
	UPROPERTY()
	TArray<int32> FrameScores;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 NumberOfRounds=10;
	UFUNCTION(BlueprintCallable)
	void ChangeFrameScore(int FrameIndex,int RoundIndex, int NewScoreValue);
	UPROPERTY(BlueprintAssignable)
	FFrameScoreChanged OnFrameScoreChanged;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Calculates the Frames scores and Final Score of the Player
	void CalculateScore();
};
