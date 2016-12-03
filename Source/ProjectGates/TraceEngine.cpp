// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGates.h"
#include "TraceEngine.h"

UTraceEngine::UTraceEngine() :
	Speed(5), 
	InsertedTraceIndex(0), 
	InsertedGateIndex(0), 
	TraceProductionSize(2), 
	TraceProduced(TraceProductionSize),
	IsGateInserted(false)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void UTraceEngine::BeginPlay()
{
	Super::BeginPlay();

	PositionTraces();
}

void UTraceEngine::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	MoveDownComponents();
	InsertComponentIfPossible();
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

		// First inserted trace pivot point will be placed at the top-center of the background bounds.
		// Other traces to be inserted will follow from there.
		float LocationZ = BackgroundBounds.Z - (BoxExtent.Z * 2) * i;
		FVector NewLocation = FVector(0, 50, LocationZ);

		Trace->SetActorLocation(NewLocation);
	}
}

bool UTraceEngine::IsInsertedTraceInsideBounds() const
{
	AActor* Trace = TraceChildActorComponents[InsertedTraceIndex]->GetChildActor();

	FVector Origin;
	FVector BoxExtent;
	Trace->GetActorBounds(false, OUT Origin, OUT BoxExtent);

	float TraceLocationZ = Trace->GetActorLocation().Z;

	return (TraceLocationZ <= BackgroundBounds.Z - BoxExtent.Z);
}

bool UTraceEngine::IsInsertedGateInsideBounds() const
{

	ULogicGate* Gate = GateComponents[InsertedGateIndex];

	FVector BoxExtent = Gate->Bounds.BoxExtent;

	return (Gate->RelativeLocation.Z <= (BackgroundBounds.Z - BoxExtent.Z));
}

/** Recycle by getting the oldest trace inserted and re-insert it. */
void UTraceEngine::InsertTrace()
{
	AActor* Trace = TraceChildActorComponents[InsertedTraceIndex]->GetChildActor();

	FVector Origin;
	FVector BoxExtent;
	Trace->GetActorBounds(false, OUT Origin, OUT BoxExtent);

	// Find the trace at the end of the line.
	int EndTraceIndex = (InsertedTraceIndex == 0) ?
		(TraceCacheCount - 1) :
		(InsertedTraceIndex + (TraceCacheCount)) % (TraceCacheCount)-1;

	// Attach the last trace to the top of the line.
	AActor* EndTrace = TraceChildActorComponents[EndTraceIndex]->GetChildActor();
	EndTrace->SetActorLocation(FVector(0, 50, BackgroundBounds.Z + BoxExtent.Z));

	// End trace is now the new start trace.
	InsertedTraceIndex = EndTraceIndex;
}

/** Recycle by getting the oldest gate inserted and re-insert it. */
void UTraceEngine::InsertGate()
{
	// Find the index of the next available gate to be recycled.
	InsertedGateIndex = (InsertedGateIndex == (GateCacheCount - 1)) ? 0 : InsertedGateIndex + 1;
	ULogicGate* Gate = GateComponents[InsertedGateIndex];
	
	Gate->SetGateType(EGateType::AND);

	FVector BoxExtent = Gate->Bounds.BoxExtent;

	// Place the gate at the top-center of the background bounds.
	FVector NewLocation = FVector(0, 75, BackgroundBounds.Z + BoxExtent.Z);
	Gate->SetRelativeLocation(NewLocation);
}

/** Move down this objects components, such as the traces and gates based on the Speed. */
void UTraceEngine::MoveDownComponents()
{
	// Move down the traces.
	for (UChildActorComponent* TraceChildActorComponent : TraceChildActorComponents)
	{
		AActor* Trace = TraceChildActorComponent->GetChildActor();
		FVector NewLocation = Trace->GetActorLocation() - FVector(0, 0, Speed);
		Trace->SetActorLocation(NewLocation);
	}

	// Move down the gates.
	for (ULogicGate* Gate : GateComponents)
	{
		FVector NewLocation = Gate->RelativeLocation - FVector(0, 0, Speed);
		Gate->SetRelativeLocation(NewLocation);
	}
}

/**
 * Determine which component is to be inserted.
 * Once the component is identified, if the last component inserted is inside the bounds, then insert it.
 * Otherwise, do nothing.
 */
void UTraceEngine::InsertComponentIfPossible()
{
	// If true, then a trace is next in line to be inserted.
	// If false, then a gate is to be inserted.
	if (TraceProduced < TraceProductionSize)
	{
		// If the inserted trace is fully inside the background bounds, then insert another trace.
		if (IsInsertedTraceInsideBounds())
		{
			InsertTrace();
			TraceProduced++;
		}
	}
	else
	{
		// Check if a gate is already inserted following the inserted trace.
		// If no gate is inserted, then check if the inserted trace is inside the boundary.
		if (IsGateInserted)
		{
			// If inserted gate is inside the bounds, then reset the TraceProduced and in insert a new trace.
			if (IsInsertedGateInsideBounds())
			{
				InsertTrace();
				TraceProduced = 1;
				IsGateInserted = false;
			}
		}
		else if (IsInsertedTraceInsideBounds())
		{
			// Insert gate.
			InsertGate();
			IsGateInserted = true;
		}
	}
}
