// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "SLStructs.h"
#include "SLOverlapShape.generated.h"

/**
 * Structure containing information about the semantic overlap event
 */
USTRUCT()
struct FSLOverlapResult
{
	GENERATED_USTRUCT_BODY()

	// Self
	FSLEntity Self;

	// Other 
	FSLEntity Other;

	// The mesh (static or skeletal) of the other overlapping component
	TWeakObjectPtr<UMeshComponent> SelfMeshComponent;

	// The mesh (static or skeletal) of the other overlapping component
	TWeakObjectPtr<UMeshComponent> OtherMeshComponent;

	// Timestamp in seconds of the event triggering
	float Time;

	// Flag showing if Other is also of type Semantic Overlap Area
	bool bIsOtherASemanticOverlapArea;

	// Default ctor
	FSLOverlapResult() {};

	// Init constructor
	FSLOverlapResult(const FSLEntity& InSelf, const FSLEntity& InOther, float InTime, 
		bool bIsSemanticOverlapArea) :
		Self(InSelf), Other(InOther), 
		Time(InTime), bIsOtherASemanticOverlapArea(bIsSemanticOverlapArea) {};

	// Init constructor with mesh component (static/skeletal)
	FSLOverlapResult(const FSLEntity& InSelf, const FSLEntity& InOther, float InTime, 
		bool bIsSemanticOverlapArea, UMeshComponent* InSelfMeshComponent, UMeshComponent* InOtherMeshComponent) :
		Self(InSelf), Other(InOther), 
		Time(InTime), bIsOtherASemanticOverlapArea(bIsSemanticOverlapArea), 
		SelfMeshComponent(InSelfMeshComponent), OtherMeshComponent(InOtherMeshComponent) {};

	// Get result as string
	FString ToString() const
	{
		return FString::Printf(TEXT("Self:[%s] Other:[%s] Time:%f bIsOtherASemanticOverlapArea:%s StaticMeshActor:%s StaticMeshComponent:%s"),
			*Self.ToString(), *Other.ToString(), Time,
			bIsOtherASemanticOverlapArea == true ? TEXT("True") : TEXT("False"),
			OtherMeshComponent.IsValid() ? *OtherMeshComponent->GetName() : TEXT("None"));
	}
};

/** Delegate to notify that a contact begins between two semantically annotated objects */
DECLARE_MULTICAST_DELEGATE_OneParam(FSLOverlapBeginSignature, const FSLOverlapResult&);

/** Delegate to notify that a contact ended between two semantically annotated objects */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FSLOverlapEndSignature, UObject* /*Self*/, UObject* /*Other*/, float /*Time*/);

/**
 * Collision area listening for semantic collision events
 */
UCLASS(ClassGroup = SL, meta = (BlueprintSpawnableComponent), hidecategories = (HLOD, Mobile, Cooking, Navigation, Physics))
class USEMLOG_API USLOverlapShape : public UBoxComponent
{
	GENERATED_BODY()
public:
	// Default constructor
	USLOverlapShape();

	// Dtor
	~USLOverlapShape();

	// Initialize trigger area for runtime, check if outer is valid and semantically annotated
	void Init();

	// Start publishing overlap events, trigger currently overlapping objects
	void Start();

	// Stop publishing overlap events
	void Finish(bool bForced = false);

	// Get init state
	bool IsInit() const { return bIsInit; };

	// Get started state
	bool IsStarted() const { return bIsStarted; };

	// Get finished state
	bool IsFinished() const { return bIsFinished; };

protected:
	// Called at level startup
	virtual void BeginPlay() override;

	// Called when actor removed from game or game ended
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITOR
private:
	// UObject interface
	// Called after the C++ constructor and after the properties have been initialized
	virtual void PostInitProperties() override;

	// Called when a property is changed in the editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface

	// USceneComponent interface
	// Called when this component is moved in the editor
	virtual void PostEditComponentMove(bool bFinished) override;
	// End of USceneComponent interface

	// Load and apply cached parameters from tags
	bool LoadShapeBounds();

	// Calculate and apply trigger area size
	bool CalcShapeBounds();

	// Save current parameters to tags
	bool StoreShapeBounds();

public:
	// Update bounds visual (red/green -- parent is not/is semantically annotated)
	// it is public so it can be accessed from the editor panel for updates
	void UpdateVisualColor();
#endif // WITH_EDITOR

private:
	// Publish currently overlapping components
	void TriggerInitialOverlaps();

	// Event called when something starts to overlaps this component
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// Event called when something stops overlapping this component 
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

public:
	// Event called when a semantic overlap begins
	FSLOverlapBeginSignature OnBeginSLOverlap;

	// Event called when a semantic overlap ends
	FSLOverlapEndSignature OnEndSLOverlap;

private:
	// True if initialized
	bool bIsInit;

	// True if started
	bool bIsStarted;

	// True if finished
	bool bIsFinished;

	// Init and start at begin play
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bStartAtBeginPlay;

	// Pointer to the outer (owner) mesh component 
	UMeshComponent* OwnerMeshComp;

	// Semantic data of the owner
	FSLEntity SemanticOwner;
};
