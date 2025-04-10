// Copyright Test Company, Inc. All Rights Reserved.


#include "BowlingScoreGame/Public/Core/BowlingScoreFinalFrame.h"

UBowlingScoreFinalFrame::UBowlingScoreFinalFrame()
{
	RoundScores.Init(0,3);
}

EFrameTypeScore UBowlingScoreFinalFrame::ValidateFrame()
{
	const int ScoredPins=RoundScores[0]+RoundScores[1]+RoundScores[2];
	if (ScoredPins>30)
	{
		RoundScores[0]=0;
		RoundScores[1]=0;
		RoundScores[2]=0;
		return EFrameTypeScore::Normal;
	}

	if (RoundScores[0]==10&&RoundScores[1]==10)
	{
		return EFrameTypeScore::Strike;
	}

	if (RoundScores[0]==10)
	{
		return EFrameTypeScore::Strike;
	}

	if ((RoundScores[0]+RoundScores[1])==10)
	{
		return EFrameTypeScore::Spare;
	}

	return EFrameTypeScore::Normal;
}

int UBowlingScoreFinalFrame::AddRoundsScores()
{
	switch (ValidateFrame())
	{
	case EFrameTypeScore::Normal:
		return RoundScores[0]+RoundScores[1];
		break;
	case EFrameTypeScore::Spare:
		return RoundScores[0]+RoundScores[1]+RoundScores[2];
		break;
	case EFrameTypeScore::Strike:
		return RoundScores[0]+RoundScores[1]+RoundScores[2];
		break;
	}
	return 0;
	
}
