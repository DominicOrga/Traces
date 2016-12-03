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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int GateCacheCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TraceCacheCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<ULogicGate*> GateComponents;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<UChildActorComponent*> TraceChildActorComponents;

private:
	/* Movement speed of the traces and gates. */
	float Speed;

	/* The index of the newly inserted trace. */
	int InsertedTraceIndex;

	/* The index of the newly inserted gate. */
	int InsertedGateIndex;

	/* The number of traces to be produced every after gate insertion. */
	int TraceProductionSize;

	/* The number of traces produced. Resets when a gate is inserted. */
	int TraceProduced;

	/* True when a gate is inserted. Resets to false when a trace is inserted. */
	bool IsGateInserted;

public:	
	UTraceEngine();

	virtual void BeginPlay() override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Initialize the position of each available cached traces into a straight line. */
	UFUNCTION(BlueprintCallable, Category="Utilities")
	void PositionTraces();

	/** Get the bounds of the background from the owner to determine where the generated objects are bounded. */
	UFUNCTION(BlueprintImplementableEvent)
	void SetBackgroundBounds();

	bool IsInsertedTraceInsideBounds() const;

	bool IsInsertedGateInsideBounds() const;

	/** Recycle by getting the oldest trace inserted and re-insert it. */
	void InsertTrace();

	/** Recycle by getting the oldest gate inserted and re-insert it. */
	void InsertGate();

	/** Move down this objects components, such as the traces and gates based on the Speed. */
	void MoveDownComponents();

	/** 
	 * Determine which component is to be inserted. 
	 * Once the component is identified, if the last component inserted is inside the bounds, then insert it.
	 * Otherwise, do nothing.
	 */
	void InsertComponentIfPossible();
};
