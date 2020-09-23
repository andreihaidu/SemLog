// Copyright 2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Viz/SLVizStructs.h"
#include "SLVizBaseMarker.generated.h"

// Forward declarations
class USLVizAssets;
class UMaterialInstanceDynamic;

/**
 * Base class of the marker visualization, acts as an interface class
 */
UCLASS()
class USEMLOG_API USLVizBaseMarker : public USceneComponent
{
	GENERATED_BODY()

public:
	// Constructor
	USLVizBaseMarker();

	// Update the visual color property
	void UpdateMaterialColor(const FLinearColor& InColor);

	// Update the material type
	void UpdateMaterialType(ESLVizMaterialType InType);

	//~ Begin ActorComponent Interface
	// Unregister the component, remove it from its outer Actor's Components array and mark for pending kill
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
	//~ End ActorComponent Interface

	/* Begin VizMarker interface */
	// Reset visuals and poses
	virtual void Reset() {};

protected:
	// Reset visual related data
	virtual void ResetVisuals() {};

	// Reset instances (poses of the visuals)
	virtual void ResetPoses() {};
	/* End VizMarker interface */

	// Create the dynamic material
	void SetDynamicMaterial(ESLVizMaterialType InType);

	// Set the color of the dynamic material
	void SetDynamicMaterialColor(const FLinearColor& InColor);

private:
	// Load assets container
	bool LoadAssetsContainer();

protected:
	// Used for applying custom materials (colors) to the marker
	//UPROPERTY(VisibleAnywhere, Transient, Category = "Semantic Logger")
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	// Dynamic material type
	ESLVizMaterialType MaterialType;

	// Dynamic material current color
	FLinearColor VisualColor;

	// Stores the predefined assets used by the markers (materials, meshes)
	USLVizAssets* VizAssetsContainer;

	/* Constants */
	static constexpr auto AssetsContainerPath = TEXT("SLVizAssets'/USemLog/Viz/SL_VizAssetsContainer.SL_VizAssetsContainer'");
};
