// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trace.h"
#include "Components/ActorComponent.h"
#include "TraceEngine.generated.h"

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGATES_API UTraceEngine : public UActorComponent
{
	GENERATED_BODY()

private:
	/* The boundary where the generated objectsts are allowed to exist. */
	UBoxComponent* TraceBoundary;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<ATrace*> Traces;

	UPROPERTY(EditAnywhere)
	UClass* BPTrace;

public:	
	// Sets default values for this component's properties
	UTraceEngine();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Check if the owner has a Box Collision Component for encapsulation of the engine's generated objects. */
	void FindTraceBoundary();
};
