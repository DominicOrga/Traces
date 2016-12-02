// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGates.h"
#include "Trace.h"

// Sets default values
ATrace::ATrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("Trace Object created."));
}

// Called when the game starts or when spawned
void ATrace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrace::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}
