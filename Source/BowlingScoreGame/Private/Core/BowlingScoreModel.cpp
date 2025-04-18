// Copyright Test Company, Inc. All Rights Reserved.


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
	//we add 9 normal score frames and then add the final score frame.
	for (int i = 0; i < 9; i++)
	{
		BowlingFrames.Add(NewObject<UBowlingScoreFrame>());
	}
	
	FrameScores.Init(0,10);
	BowlingFrames.Add(NewObject<UBowlingScoreFinalFrame>());
}
// check each Frame and get the final score value
void ABowlingScoreModel::CalculateScore()
{
	 FrameIndex=0;
	uint16 TotalScore=0;
	 constexpr int NumberOfRounds=9;
	while (FrameIndex<=NumberOfRounds)
	{
		switch (BowlingFrames[FrameIndex]->ValidateFrame())
		{
		case EFrameTypeScore::Normal:
			FrameScores[FrameIndex] = BowlingFrames[FrameIndex]->AddRoundsScores();
			break;
		case EFrameTypeScore::Spare:
			if (FrameIndex==NumberOfRounds)
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores();
			}else
			{
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->RoundScores[0];
			}
			break;
		case EFrameTypeScore::Strike:
			//strikes edge cases when we are on last 3 frames
			//when its the last frame
			if (FrameIndex==NumberOfRounds)
			{
				FrameScores[FrameIndex]= BowlingFrames[FrameIndex]->AddRoundsScores();
			}else if (FrameIndex==NumberOfRounds-1)
			{
				FrameScores[FrameIndex]= BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->RoundScores[0]+BowlingFrames[FrameIndex+1]->RoundScores[1];
				
			}
			else if (FrameIndex==NumberOfRounds-2)
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
				FrameScores[FrameIndex]=BowlingFrames[FrameIndex]->AddRoundsScores()+BowlingFrames[FrameIndex+1]->AddRoundsScores();
			}
			break;
		}
		//We add to total score the frame score, and then we broadcast the change so that any system can get the score of a frame
		TotalScore+=FrameScores[FrameIndex];
		OnFrameScoreChanged.Broadcast(FrameIndex,FrameScores[FrameIndex],TotalScore);
		FrameIndex++;
	}

	
}



