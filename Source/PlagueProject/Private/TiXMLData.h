#pragma once

#include <map> 

#include "Plugins/TinyXML/tinyxml.h"
#include "FSubtitleData.h"
#include "FSpeakerData.h"
#include "CoreMinimal.h"
#include "TiXMLData.generated.h"


UCLASS()
class UTiXMLData : public UObject
{
	GENERATED_BODY()

public:

/** Constructor **/
	static UTiXMLData* Make(const FString& filePath);


/** Functions **/
	UFUNCTION(BlueprintCallable, Category = "TinyXMLHelper")
	bool ParseXMLFileAsSubtitle();

	UFUNCTION(BlueprintCallable, Category = "TinyXMLHelper")
	bool ParseXMLFileAsSpeaker();

	UFUNCTION(BlueprintCallable, Category = "TinyXMLHelper")
	TArray<FSubtitleData> GetSubtitleData(int groupId);

	UFUNCTION(BlueprintCallable, Category = "TinyXMLHelper")
	FSpeakerData GetSpeakerData(int speakerId);

/** Variables **/
	UPROPERTY(BlueprintReadOnly, Category="TinyXMLData")
	bool LoadSuccessfully;

	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	TArray<int> LoadedSubtitleGroupIds;

	UPROPERTY(BlueprintReadOnly, Category = "TinyXMLData")
	TArray<int> LoadedSpeakerIds;

	std::map<int, TArray<FSubtitleData>> GroupIdToSubtitleDataMap;
	std::map<int, FSpeakerData> SpeakerIdToSpeakerDataMap;
	const FString* FilePath;
	TiXmlDocument* XmlDocument;
	TiXmlElement* XmlRootElem;
};