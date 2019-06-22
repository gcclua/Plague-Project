#pragma once

#include "CoreMinimal.h"
#include "FSpeakerData.generated.h"


USTRUCT(Blueprintable)
struct FSpeakerData
{
	GENERATED_BODY()

/** Constructor **/
	FSpeakerData()
	{
		Name = NULL;
	}

	FSpeakerData(FString& _name)
	{
		Name = _name;
	}
	
/** Variables **/
	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	FString Name;
};