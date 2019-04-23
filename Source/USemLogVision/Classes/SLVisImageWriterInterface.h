// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SLVisHelpers.h" // ESLVisRenderType
#include "SLVisImageWriterInterface.generated.h"


/**
* Parameters for creating an image data writer
*/
struct FSLVisImageWriterParams
{
	// Location where to save the data (filename/database name etc.)
	FString Location;

	// Episode unique id
	FString EpisodeId;

	// Server ip (optional)
	FString ServerIp;

	// Server Port (optional)
	uint16 ServerPort;

	// Minimum time offset for a new entry
	float SkipNewEntryTolerance;

	// Constructor
	FSLVisImageWriterParams(
		const FString& InLocation,
		const FString& InEpisodeId,
		float InSkipNewEntryTolerance = 0.f,
		const FString& InServerIp = "",
		uint16 InServerPort = 0) :
		Location(InLocation),
		EpisodeId(InEpisodeId),
		SkipNewEntryTolerance(InSkipNewEntryTolerance),
		ServerIp(InServerIp),
		ServerPort(InServerPort)
	{};
};


/**
* Images metadatadata
*/
struct FSLVisImageMetaData
{
	// Render type
	FString RenderType;

	// Image type
	FString ImageType; //png, depth resolution?
};



/**
* Images data 
*/
struct FSLVisImageData
{
	// Default ctor
	FSLVisImageData() {};

	// Init ctor
	FSLVisImageData(ESLVisRenderType InRenderType, const TArray<uint8>& InBinaryData) : RenderType(InRenderType), BinaryData(InBinaryData) {};

	// TODO use FSLVisImageMetaData when more data is available
	// Render type
	ESLVisRenderType RenderType;

	// Binary data
	TArray<uint8> BinaryData;
};


/**
* Semantic entities data from the view
*/
struct FSLVisEntitiyData
{
	// Default ctor
	FSLVisEntitiyData() : NumPixels(0) {};

	// Color
	FColor Color;

	// Color in hex
	FString ColorHex;

	// Unique id of the entity
	FString Id;

	// Class of the entity
	FString Class;

	// Number of pixels belonging to the entity from the image
	int32 NumPixels;

	FString ToString() const
	{
		return FString::Printf(TEXT("Color=%s; ColorHex=%s; Id=%s; Class=%s; NumPixels=%d;"),
			*Color.ToString(), *ColorHex, *Id, *Class, NumPixels);
	}
};

/**
* Semantic skeletal entities data from the view
*/
struct FSLVisBoneData
{
	// Default ctor
	FSLVisBoneData() : NumPixels(0) {};

	// TODO OwnerId and OwnerClass is redundant since skel data also contains this
	// it is convenient however for fast TMap lookups when processing the mask image pixels
	// Owner Id
	FString OwnerId;

	// Owner Class
	FString OwnerClass;

	// Color
	FColor Color;

	// Color in hex
	FString ColorHex;

	// Class of the bone
	FString Class;

	// Number of pixels belonging to the entity from the image
	int32 NumPixels;

	FString ToString() const
	{
		return FString::Printf(TEXT("Color=%s; ColorHex=%s; Class=%s; NumPixels=%d;"),
			*Color.ToString(), *ColorHex, *Class, NumPixels);
	}

	// Check if two bones data is equal (comparing the colors should be the fastest, since the color should be unique)
	bool operator==(const FSLVisBoneData& Other) const
	{
		return Color == Other.Color;
	}
};

/**
* Semantic skeletal entities data from the view
*/
struct FSLVisSkelData
{
	// Default ctor
	FSLVisSkelData() {};

	// Init ctor
	FSLVisSkelData(const FString& InId, const FString& InClass) : Id(InId), Class(InClass) {};

	// Unique id of the entity
	FString Id;

	// Class of the entity
	FString Class;

	// Bones data
	TArray<FSLVisBoneData> BonesData;

	FString ToString() const
	{
		return FString::Printf(TEXT("Id=%s; Class=%s; NumBonedData=%d; Class=%s; NumPixels=%d;"),
			*Id, *Class, BonesData.Num());
	}
};


/**
* Data data from the view
*/
struct FSLVisViewData
{
	// Default ctor
	FSLVisViewData() {};

	// Id of the current view
	FString Id;

	// Name of the current view
	FString Class;

	// Image resolution
	FIntPoint Resolution;

	// Data about the entities visible in the view
	TArray<FSLVisEntitiyData> SemanticEntities;

	// Data about the skeletal entities visible in the view
	TArray<FSLVisSkelData> SemanticSkelEntities;

	// Image data of the given render type
	TArray<FSLVisImageData> ImagesData;

	// Get init state
	bool IsInit() const { return bIsInit; };

	// Init view data
	void Init(const FString& InId, const FString& InClass, const FIntPoint& InResolution)
	{
		Id = InId;
		Class = InClass;
		Resolution = InResolution;
		bIsInit = true;
	}

	// Clear all data
	void Reset()
	{
		Id = FString();
		Class = FString();
		Resolution = FIntPoint(ForceInitToZero);
		SemanticEntities.Empty();
		ImagesData.Empty();
		bIsInit = false;
	}

private:
	// Init state flag
	bool bIsInit;
};


/**
* Collection of all the views data in the current rendered timestamp
*/
struct FSLVisStampedData
{
	// The timestamp when the images are rendered
	float Timestamp;

	// Array of the camera views data
	TArray<FSLVisViewData> ViewsData;

	// Reset the data
	void Reset()
	{
		Timestamp = 0.f;
		ViewsData.Empty();
	}

	// Debug string
	FString ToString() const
	{
		return FString::Printf(TEXT("Timestamp=%f; ViewsData.Num()=%d"), Timestamp, ViewsData.Num());
	}
};


/**
* Dummy class needed to support Cast<ISLVisImageWriterInterface>(Object).
*/
UINTERFACE(Blueprintable)
class USLVisImageWriterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Base class for image data writer
 */
class ISLVisImageWriterInterface
{
	GENERATED_BODY()

public:
	// Init the writer
	virtual void Init(const FSLVisImageWriterParams& InParams) = 0;

	// Called when done writing
	virtual void Finish() = 0;

	// Write the images at the timestamp
	virtual void Write(const FSLVisStampedData& StampedData) = 0;

	// True if the writer is valid
	bool IsInit() const { return bIsInit; }

protected:
	// Flag to show if it is valid
	bool bIsInit;
	// Flag to show if mongoc has been called
	bool bIsMongoInitCalled;
};
