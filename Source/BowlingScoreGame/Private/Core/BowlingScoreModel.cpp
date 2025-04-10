// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingScoreGame/Public/Core/BowlingScoreModel.h"
#include "BowlingScoreGame/Public/Core/BowlingScoreFinalFrame.h"



ABowlingScoreModel::ABowlingScoreModel()
{
	// our actor does not need the tick function 
	PrimaryActorTick.bCanEverTick = false;
}

ABowlingScoreModel::~ABowlingScoreModel()
{
	//Clear our delegate and two TArrays
	OnFrameScoreChanged.Clear();
	if (BowlingFrames.Num()>0)
	{
		BowlingFrames.Empty();
		FrameScores.Empty();
	}
}

//Utilize it to change any position inside the model Frame
void ABowlingScoreModel::ChangeFrameScore(int FramePosition, int RoundPosition, int32 NewScoreValue)
{
	BowlingFrames[FramePosition]->RoundScores[RoundPosition] = NewScoreValue;
	
	CalculateScore();
}

// Called when the game starts or when spawned
void ABowlingScoreModel::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 9; i++)
	{
		BowlingFrames.Add(NewObject<UBowlingScoreFrame>());
	}
	
	FrameScores.Init(0,10);
	BowlingFrames.Add(NewObject<UBowlingScoreFinalFrame>());
}
// check each Frame
void ABowlingScoreModel::CalculateScore()
{
	 FrameIndex=0;
	uint16 TotalScore=0;
	while (FrameIndex<=9)
	{
		switch (BowlingFrames[FrameIndex]->ValidateFrame())
		{
		case EFrameTypeScore::Normal:
			FrameScores[FrameIndex] = BowlingFrames[FrameIndex]->AddRoundsScores();
			break;
		case EFrameTypeScore::Spare:
			if (FrameIndex==9)
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores();
			}else
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->RoundScores[0];
			}
			break;
		case EFrameTypeScore::Strike:
			if (FrameIndex==9)
			{
				FrameScores[FrameIndex]= BowlingFrames[FrameIndex]->AddRoundsScores();
			}else if (FrameIndex==8)
			{
				FrameScores[FrameIndex]= BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->RoundScores[0]+BowlingFrames[FrameIndex+1]->RoundScores[1];
				
			}
			else if (FrameIndex==7)
			{
				
				if (BowlingFrames[FrameIndex+1]->ValidateFrame()==EFrameTypeScore::Strike)
				{
					FrameScores[FrameIndex]= BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->AddRoundsScores()+BowlingFrames[FrameIndex+2]->RoundScores[1];
				}
				else
				{
					FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores();
				}
			}
			else if (BowlingFrames[FrameIndex+1]->ValidateFrame()==EFrameTypeScore::Strike&&BowlingFrames[FrameIndex+2]->ValidateFrame()==EFrameTypeScore::Strike)
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->AddRoundsScores()+BowlingFrames[FrameIndex+2]->AddRoundsScores();
			}
			else if (BowlingFrames[FrameIndex+1]->ValidateFrame()==EFrameTypeScore::Strike||BowlingFrames[FrameIndex+1]->ValidateFrame()==EFrameTypeScore::Spare)
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->AddRoundsScores();
			}
			else
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores();
			}
			break;
		}

		TotalScore+=FrameScores[FrameIndex];
		UE_LOG(LogTemp, Display, TEXT("Total Score: %d"), TotalScore);
		OnFrameScoreChanged.Broadcast(FrameIndex,FrameScores[FrameIndex],TotalScore);
		FrameIndex++;
	}

	
}



