#include "TiXMLData.h"
#include "TinyXMLHelper.h"

#include <string>
#include <codecvt>



UTiXMLData* UTiXMLData::Make(const FString& filePath)
{
	UTiXMLData* data = NewObject<UTiXMLData>();

	data->FilePath = &filePath;
	data->XmlDocument = NULL;
	data->XmlRootElem = NULL;

	char* path = TCHAR_TO_ANSI(*filePath);

	data->XmlDocument = new TiXmlDocument(path);
	data->LoadSuccessfully = data->XmlDocument->LoadFile();
	if (!(data->LoadSuccessfully))
	{
		return nullptr;
	}

	if (data->LoadSuccessfully && data->XmlDocument->ErrorId() > 0)
	{
		return nullptr;
	}

	data->XmlRootElem = data->XmlDocument->RootElement();
	return data;
}


/*--------------------------------------------------------------------------------------------------------*/


bool UTiXMLData::ParseXMLFileAsSubtitle()
{
	if (!XmlRootElem)
		return false;
	
	for (TiXmlElement* elem = XmlRootElem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string elemName = elem->Value();
		if ( UTinyXMLHelper::StringComparisonCaseInsensitive(elemName, "group") )
		{
			int groupId = UTinyXMLHelper::ToInt(elem, "id");
			TArray<FSubtitleData> dataArray;
			
			for (TiXmlElement* subElem = elem->FirstChildElement(); subElem != NULL; subElem = subElem->NextSiblingElement())
			{
				elemName = subElem->Value();
				if ( UTinyXMLHelper::StringComparisonCaseInsensitive(elemName, "subtitle") )
				{
					std::string unicodeText = subElem->GetText();
					FString text = UTF8_TO_TCHAR(unicodeText.c_str());
					int speakerId = UTinyXMLHelper::ToInt(subElem, "speaker_id");
					bool block = UTinyXMLHelper::ToBool(subElem, "block");
					float duration = UTinyXMLHelper::ToFloat(subElem, "duration");

					FSubtitleData data(text, speakerId, block, duration);
					dataArray.Add(data);
				}
			}

			GroupIdToSubtitleDataMap.emplace(groupId, dataArray);
			LoadedSubtitleGroupIds.Add(groupId);
		}
	}
	return true;
}


/*--------------------------------------------------------------------------------------------------------*/


bool UTiXMLData::ParseXMLFileAsSpeaker()
{
	if (!XmlRootElem)
		return false;

	for (TiXmlElement* elem = XmlRootElem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string elemName = elem->Value();
		if (UTinyXMLHelper::StringComparisonCaseInsensitive(elemName, "speaker"))
		{
			int speakerId = UTinyXMLHelper::ToInt(elem, "id");
			std::string unicodeText = elem->GetText();
			FString name = UTF8_TO_TCHAR(unicodeText.c_str());

			FSpeakerData data(name);
			SpeakerIdToSpeakerDataMap.emplace(speakerId, data);
			LoadedSpeakerIds.Add(speakerId);
		}
	}
	return true;
}


/*--------------------------------------------------------------------------------------------------------*/


TArray<FSubtitleData> UTiXMLData::GetSubtitleData(int groupId)
{
	if (GroupIdToSubtitleDataMap.find(groupId) == GroupIdToSubtitleDataMap.end())
		return TArray<FSubtitleData>();

	return GroupIdToSubtitleDataMap[groupId];
}


/*--------------------------------------------------------------------------------------------------------*/


FSpeakerData UTiXMLData::GetSpeakerData(int speakerId)
{
	if (SpeakerIdToSpeakerDataMap.find(speakerId) == SpeakerIdToSpeakerDataMap.end())
		return FSpeakerData();

	return SpeakerIdToSpeakerDataMap[speakerId];
}