// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyXMLHelper.h"

UTiXMLData* UTinyXMLHelper::LoadXMLFile(const FString& filePath)
{
	UTiXMLData* data = UTiXMLData::Make(filePath);
	return data;
}

int UTinyXMLHelper::ToInt(const TiXmlElement* elem, const char* attributeName)
{
	return (elem->Attribute(attributeName) == NULL ? 0 : atoi(elem->Attribute(attributeName)));
}


float UTinyXMLHelper::ToFloat(const TiXmlElement* elem, const char* attributeName)
{
	return (elem->Attribute(attributeName) == NULL ? 0.0f : (float)atof(elem->Attribute(attributeName)));
}


char* UTinyXMLHelper::ToString(const TiXmlElement* elem, const char* attributeName)
{
	return (elem->Attribute(attributeName) == NULL ? "" : elem->Attribute(attributeName));
}


bool UTinyXMLHelper::ToBool(const TiXmlElement* elem, const char* attributeName, bool fromString)
{
	return (elem->Attribute(attributeName) == NULL ? false : (fromString ? atoi(elem->Attribute(attributeName)) : StringComparisonCaseInsensitive(elem->Attribute(attributeName), "true")));
}


bool UTinyXMLHelper::IsValid(const TiXmlElement* elem, const char* attributeName)
{
	if (elem->Attribute(attributeName) == NULL)
		return false;
	return true;
}


inline bool UTinyXMLHelper::CharComparisonCaseInsensitive(char a, char b)
{
	return(toupper(a) == toupper(b));
}


bool UTinyXMLHelper::StringComparisonCaseInsensitive(const std::string& s1, const std::string& s2)
{
	return((s1.size() == s2.size()) && equal(s1.begin(), s1.end(), s2.begin(), CharComparisonCaseInsensitive));
}