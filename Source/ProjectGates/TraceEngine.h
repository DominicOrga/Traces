// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LogicGate.h"
#include "Trace.h"
#include "Components/ActorComponent.h"
#include "TraceEngine.generated.h"

#define OUT

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGATES_API UTraceEngine : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	FVector BackgroundBounds;

	/* The total number of gates to cache. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int GateCacheCount;

	/* The total number of traces to cache. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TraceCacheCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<ULogicGate*> GateComponents;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<UChildActorComponent*> TraceChildActorComponents;

private:
	float Momentum;

	int StartTraceIndex;
	int GateIndex;

	int TraceProductionSize;
	int TraceProduced;

	UObject* LatestAddedComponent;

	bool IsGateAdded;

public:	
	// Sets default values for this component's properties
	UTraceEngine();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Initialize the position of each available cached traces into a straight line. */
	UFUNCTION(BlueprintCallable, Category="Utilities")
	void PositionTraces();

	/** Get the bounds of the background from the owner to determine where the generated objects are bounded. */
	UFUNCTION(BlueprintImplementableEvent)
	void SetBackgroundBounds();

	/** Move down the traces based on the Momentum. */
	void MoveDownTraces();

	bool CheckStartTraceInsideBgBounds();

	void AttachEndTraceToStart();

	bool CheckGateInsideBgBounds();
};
