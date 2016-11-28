// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trace.h"
#include "GameFramework/Actor.h"
#include "GatesClassic.generated.h"

UCLASS()
class PROJECTGATES_API AGatesClassic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGatesClassic();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
