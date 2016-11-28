// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Trace.generated.h"

UENUM(BlueprintType)
enum class ETraceDirection : uint8
{
	Straight UMETA(DisplayName="Straight Trace"),
	LeftCurvedStraight UMETA(DisplayName="Left Curved Straight Trace"),
	RightCurvedStraight UMETA(DisplayName="Right Curved Straight Trace"),
	RightCurve UMETA(DisplayName=" Right Curve Trace"),
	LeftStraightRightCurve UMETA(DisplayName="Left Straight Right Curve Trace"),
	LeftCurve UMETA(DisplayName="Left Curve Trace"),
	RightStraightLeftCurve UMETA(DisplayName="Right Straight Left Curve Trace")
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

	UFUNCTION(BlueprintImplementableEvent)
	void SetTraceDirection(ETraceDirection TraceDirection);
};
