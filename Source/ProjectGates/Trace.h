
#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Trace.generated.h"

UENUM(BlueprintType)
enum class ETraceType : uint8
{
	Complete UMETA(DisplayName = "Complete"),
	RightOnly UMETA(DisplayName = "RightOnly"),
	LeftOnly UMETA(DisplayName = "LeftOnly")
};

UCLASS(abstract, BlueprintType)
class PROJECTGATES_API ATrace : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPaperSpriteComponent* LeftTrace;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPaperSpriteComponent* RightTrace;

private: 
	UPROPERTY(EditDefaultsOnly)
	float TraceDistance;

public:	
	// Sets default values for this actor's properties
	ATrace();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Set the type of trace this object will represent. */
	UFUNCTION(BlueprintImplementableEvent)
	void SetTraceType(ETraceType TraceType);
};
