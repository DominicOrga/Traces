// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "LogicGate.generated.h"

UENUM(BlueprintType)
enum class EGateType : uint8
{
	AND UMETA(DisplayName = "AND"),
	NAND UMETA(DisplayName = "NAND"),
	OR UMETA(DisplayName = "OR"),
	NOR UMETA(DisplayName = "NOR"),
	XOR UMETA(DisplayName = "XOR")
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class PROJECTGATES_API ULogicGate : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetGateType(EGateType GateType);
	
};
