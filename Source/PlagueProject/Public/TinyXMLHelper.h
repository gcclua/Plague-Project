#pragma once

#include "TiXMLData.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TinyXMLHelper.generated.h"


UCLASS()
class PLAGUEPROJECT_API UTinyXMLHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TinyXMLHelper")
	static UTiXMLData* LoadXMLFile(const FString& filePath);

	static int ToInt(const TiXmlElement* elem, const char* attributeName);
	static float ToFloat(const TiXmlElement* elem, const char* attributeName);
	static char* ToString(const TiXmlElement* elem, const char* attributeName);
	static bool ToBool(const TiXmlElement* elem, const char* attributeName, bool fromString = false);
	static bool IsValid(const TiXmlElement* elem, const char* attributeName);
	static inline bool CharComparisonCaseInsensitive(char a, char b);
	static bool StringComparisonCaseInsensitive(const std::string& s1, const std::string& s2);
};
