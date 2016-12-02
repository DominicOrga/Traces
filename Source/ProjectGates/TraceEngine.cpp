// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGates.h"
#include "TraceEngine.h"

// Sets default values for this component's properties
UTraceEngine::UTraceEngine() :
	Momentum(5), StartTraceIndex(0)
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

	InstantiateTraces();
	PositionTraces();
}

// Called every frame
void UTraceEngine::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	MoveDownTraces();

	// If the current start trace is fully inside the background bounds,
	//		then set the last trace as the new start trace and attach it to the top.
	if (CheckStartTraceInsideBgBounds())
	{
		AttachEndTraceToStart();
	}

}

/** Instantiate and cache traces based on the TraceCacheCount. */
void UTraceEngine::InstantiateTraces()
{
	for (int i = 0; i < TraceCacheCount; i++)
	{
		UChildActorComponent* TraceChildActorComponent = 
			NewObject<UChildActorComponent>(GetOwner(), UChildActorComponent::StaticClass());

		TraceChildActorComponent->SetChildActorClass(TraceBP);
		TraceChildActorComponent->CreateChildActor();

		TraceChildActorComponents.Emplace(TraceChildActorComponent);
	}
}

/** Initialize the position of each available cached traces into a vertical line. */
void UTraceEngine::PositionTraces()
{
	for (int i = 0; i < TraceCacheCount; i++)
	{
		ATrace* Trace = Cast<ATrace>(TraceChildActorComponents[i]->GetChildActor());

		// Set each trace object type as complete, since trace objects do not have types by default.
		Trace->SetTraceType(ETraceType::Complete);

		FVector Origin;
		FVector BoxExtent;
		Trace->GetActorBounds(false, OUT Origin, OUT BoxExtent);

		// First trace pivot point will be placed at the top-center of the background bounds.
		// Following trace will follow from there.
		float LocationZ = BackgroundBounds.Z - (BoxExtent.Z * 2) * i;
		FVector NewLocation = FVector(0, 50, LocationZ);

		Trace->SetActorLocation(NewLocation);
	}
}

/** Move down the traces based on the Momentum. */
void UTraceEngine::MoveDownTraces()
{
	for (UChildActorComponent* TraceChildActorComponent : TraceChildActorComponents)
	{
		AActor* Trace = TraceChildActorComponent->GetChildActor();
		FVector NewLocation = Trace->GetActorLocation() - FVector(0, 0, Momentum);
		Trace->SetActorLocation(NewLocation);
	}
}

bool UTraceEngine::CheckStartTraceInsideBgBounds()
{
	AActor* Trace = TraceChildActorComponents[StartTraceIndex]->GetChildActor();

	FVector Origin;
	FVector BoxExtent;
	Trace->GetActorBounds(false, OUT Origin, OUT BoxExtent);

	float StartTraceLocationZ = Trace->GetActorLocation().Z;

	return (StartTraceLocationZ == BackgroundBounds.Z - BoxExtent.Z);
}

void UTraceEngine::AttachEndTraceToStart()
{
	AActor* Trace = TraceChildActorComponents[StartTraceIndex]->GetChildActor();

	FVector Origin;
	FVector BoxExtent;
	Trace->GetActorBounds(false, OUT Origin, OUT BoxExtent);

	// Find the trace at the end of the line.
	int EndTraceIndex = (StartTraceIndex == 0) ?
		(TraceCacheCount - 1) :
		(StartTraceIndex + (TraceCacheCount)) % (TraceCacheCount)-1;

	// Attach the last trace to the top of the line.
	AActor* EndTrace = TraceChildActorComponents[EndTraceIndex]->GetChildActor();
	EndTrace->SetActorLocation(FVector(0, 50, BackgroundBounds.Z + BoxExtent.Z));

	// End trace is now the new start trace.
	StartTraceIndex = EndTraceIndex;
}

void UTraceEngine::InstantiateGates()
{

}
