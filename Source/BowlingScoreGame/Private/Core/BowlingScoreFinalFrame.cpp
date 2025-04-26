// Copyright Test Company, Inc. All Rights Reserved.


#include "BowlingScoreGame/Public/Core/BowlingScoreFinalFrame.h"

UBowlingScoreFinalFrame::UBowlingScoreFinalFrame()
{
	RoundScores.Init(0, 3);
}

EFrameTypeScore UBowlingScoreFinalFrame::ValidateFrame()
{
	const int ScoredPins = RoundScores[0] +RoundScores[1] + RoundScores[2];
	constexpr int32 MaxFallenPins = 10;
	constexpr int32 MaxPossibleScore = 30;
	if (ScoredPins > MaxPossibleScore)
	{
		RoundScores[0] = 0;
		RoundScores[1] = 0;
		RoundScores[2] = 0;
		return EFrameTypeScore::Normal;
	}

	if (RoundScores[0] == MaxFallenPins && RoundScores[1] == MaxFallenPins)
	{
		return EFrameTypeScore::Strike;
	}

	if (RoundScores[0] == MaxFallenPins)
	{
		return EFrameTypeScore::Strike;
	}

	if ((RoundScores[0] + RoundScores[1]) == MaxFallenPins)
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
		return RoundScores[0] + RoundScores[1];
		break;
	case EFrameTypeScore::Spare:
		return RoundScores[0] + RoundScores[1] + RoundScores[2];
		break;
	case EFrameTypeScore::Strike:
		return RoundScores[0] + RoundScores[1] + RoundScores[2];
		break;
	}
	return 0;
}
