// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "LogicGate.generated.h"

UENUM(BlueprintType)
enum class EGateType : uint8
{
	AND UMETA(DisplayName = "AND")
};

UCLASS(Blueprintable)
class PROJECTGATES_API ULogicGate : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetGateType(EGateType GateType);
	
};
