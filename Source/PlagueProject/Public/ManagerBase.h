#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.generated.h"


UCLASS(Blueprintable)
class PLAGUEPROJECT_API UManagerBase : public UObject
{
	GENERATED_BODY()

	virtual class UWorld* GetWorld() const final
	{
		auto outer = GetOuter();
		if (outer)
		{
			return outer->GetWorld();
		}
		
		return NULL;
	}

};