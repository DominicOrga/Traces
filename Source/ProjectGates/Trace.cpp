// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGates.h"
#include "Trace.h"


// Sets default values
ATrace::ATrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrace::BeginPlay()
{
	Super::BeginPlay();
	
	// Seperate the left trace from the right trace based on the trace distance.
	FVector NewLeftTraceLocation = LeftTrace->RelativeLocation - FVector(TraceDistance / 2, 0, 0);
	FVector NewRightTraceLocation = RightTrace->RelativeLocation + FVector(TraceDistance / 2, 0, 0);

	LeftTrace->SetRelativeLocation(NewLeftTraceLocation);
	RightTrace->SetRelativeLocation(NewRightTraceLocation);

	UE_LOG(LogTemp, Warning, TEXT("Left Trace Location: %s"), *LeftTrace->RelativeLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Right Trace Location: %s"), *RightTrace->RelativeLocation.ToString());
}

// Called every frame
void ATrace::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

