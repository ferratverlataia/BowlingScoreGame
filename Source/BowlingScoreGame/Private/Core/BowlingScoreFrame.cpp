// Copyright Test Company, Inc. All Rights Reserved.


#include "BowlingScoreGame/Public/Core/BowlingScoreFrame.h"

UBowlingScoreFrame::UBowlingScoreFrame()
{
	RoundScores.Init(0, 2);
}

EFrameTypeScore UBowlingScoreFrame::ValidateFrame()
{
	const int32 ScoredPins = RoundScores[0] + RoundScores[1];
	constexpr int32 MaxFallenPins = 10;
	if (ScoredPins > MaxFallenPins)
	{
		RoundScores[0] = 0;
		RoundScores[1] = 0;

		return EFrameTypeScore::Normal;
	}

	if (RoundScores[0] == MaxFallenPins)
	{
		return EFrameTypeScore::Strike;
	}
	if (ScoredPins == MaxFallenPins)
	{
		return EFrameTypeScore::Spare;
	}

	return EFrameTypeScore::Normal;
}

int UBowlingScoreFrame::AddRoundsScores()
{
	return RoundScores[0] + RoundScores[1];
}
