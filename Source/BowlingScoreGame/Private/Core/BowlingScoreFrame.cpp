// Copyright Test Company, Inc. All Rights Reserved.


#include "BowlingScoreGame/Public/Core/BowlingScoreFrame.h"

UBowlingScoreFrame::UBowlingScoreFrame()
{
	RoundScores.Init(0,2);
}

EFrameTypeScore UBowlingScoreFrame::ValidateFrame()
{
	const int ScoredPins=RoundScores[0]+RoundScores[1];

	if (ScoredPins>10)
	{
		RoundScores[0]=0;
		RoundScores[1]=0;
			
		return EFrameTypeScore::Normal;
	}

	if(RoundScores[0] ==10 || RoundScores[1] ==10)
	{
		return  EFrameTypeScore::Strike;
	}
	if (ScoredPins ==10)
	{
		return EFrameTypeScore::Spare;
	}
	
	return EFrameTypeScore::Normal;

}

int UBowlingScoreFrame::AddRoundsScores()
{
	return RoundScores[0]+RoundScores[1];
}
