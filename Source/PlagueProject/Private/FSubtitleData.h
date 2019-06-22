#pragma once

#include "CoreMinimal.h"
#include "FSubtitleData.generated.h"


USTRUCT(Blueprintable)
struct FSubtitleData
{
	GENERATED_BODY()

/** Constructor **/
	FSubtitleData()
	{
		Text = NULL;
		SpeakerId = -1;
		Block = false;
		Duration = 0.0f;
	}

	FSubtitleData(FString& _text, int _speakerId, bool _block, float _duration)
	{
		Text = _text;
		SpeakerId = _speakerId;
		Block = _block;
		Duration = _duration;
	}
	
/** Variables **/
	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	FString Text;
	
	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	int32 SpeakerId;
	
	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	bool Block;
	
	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	float Duration;
};