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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector BackgroundBounds;

private:
	/* A reference to the Blueprint Trace class to instantiate traces baseed on that class. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATrace> TraceBP;

	/* The total number of traces to cache. */
	UPROPERTY(EditDefaultsOnly)
	int TraceCacheCount;

	/* The total number of gates to cache. */
	UPROPERTY(EditDefaultsOnly)
	int GateCacheCount;

	float Momentum;

	int StartTraceIndex;

	TArray<UChildActorComponent*> TraceChildActorComponents;

	TArray<ULogicGate*> GateComponents;

public:	
	// Sets default values for this component's properties
	UTraceEngine();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Instantiate and cache traces based on the TraceCacheCount. */
	void InstantiateTraces();

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

	void InstantiateGates();
};
