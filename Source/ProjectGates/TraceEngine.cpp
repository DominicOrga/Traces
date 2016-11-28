// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGates.h"
#include "TraceEngine.h"


// Sets default values for this component's properties
UTraceEngine::UTraceEngine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTraceEngine::BeginPlay()
{
	Super::BeginPlay();

	FindTraceBoundary();
	
	UChildActorComponent* Trace = ConstructObject<UChildActorComponent>(UChildActorComponent::StaticClass(), GetOwner());
	Trace->SetChildActorClass(BPTrace);
	Trace->CreateChildActor();
}

// Called every frame
void UTraceEngine::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

/** Check if the owner has a Box Collision Component for encapsulation of the engine's generated objects. */
void UTraceEngine::FindTraceBoundary()
{
	TraceBoundary = GetOwner()->FindComponentByClass<UBoxComponent>();

	if (!TraceBoundary)
	{
		UE_LOG(LogTemp, Error, TEXT("%s needs a Box Collision Component for Trace Engine."), *GetOwner()->GetName());
	}
}
