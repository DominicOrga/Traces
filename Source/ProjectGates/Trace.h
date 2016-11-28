// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Trace.generated.h"

UENUM(BlueprintType)
enum class ETraceEnum : uint8
{
	TRACE_Straight UMETA(DisplayName="Straight Trace"),
	TRACE_RightTurn UMETA(DisplayName="Right Turn Trace"),
	TRACE_LeftTurn UMETA(DisplayName="Left Turn Trace")
};

UCLASS(BlueprintType)
class PROJECTGATES_API ATrace : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UPaperSpriteComponent* LeftTrace;

	UPROPERTY(BlueprintReadWrite)
	UPaperSpriteComponent* RightTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceDistance;

public:	
	// Sets default values for this actor's properties
	ATrace();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

};
