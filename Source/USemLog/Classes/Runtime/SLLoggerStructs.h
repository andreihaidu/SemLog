// Copyright 2017-2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "SLLoggerStructs.generated.h"

/* Save location info */
USTRUCT()
struct FSLLoggerLocationParams
{
	GENERATED_BODY();

	// Set to true in order to edit the episode id
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bUseCustomTaskId = false;

	// Unique id of the task
	UPROPERTY(EditAnywhere, Category = "Semantic Logger", meta = (editcondition = "bUseCustomTaskId"))
	FString TaskId = TEXT("DefaultTaskId");

	// Set to true in order to edit the episode id
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bUseCustomEpisodeId = false;

	// Unique id of the episode
	UPROPERTY(EditAnywhere, Category = "Semantic Logger", meta = (editcondition = "bUseCustomEpisodeId"))
	FString EpisodeId = TEXT("DefaultEpisodeId");

	// Overwrite any exiting data
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bOverwrite = false;
};

/* DB Server location info */
USTRUCT()
struct FSLLoggerDBServerParams
{
	GENERATED_BODY();

	// Database Server Ip
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	FString Ip = TEXT("127.0.0.1");

	// Database server port num
	UPROPERTY(EditAnywhere, Category = "Semantic Logger", meta = (ClampMin = 0, ClampMax = 65535))
	uint16 Port = 27017;
};

/* Logger start options */
UENUM()
enum class ESLLoggerStartTime : uint8
{
	AtBeginPlay         UMETA(DisplayName = "AtBeginPlay"),
	AtNextTick			UMETA(DisplayName = "AtNextTick"),
	AfterDelay			UMETA(DisplayName = "AfterDelay"),
	FromUserInput       UMETA(DisplayName = "FromUserInput"),
};

/* Start logger info */
USTRUCT()
struct FSLLoggerStartParams
{
	GENERATED_BODY();

	// Reset start time to 0 when starting to log
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bResetStartTime = false;

	// Logger start time
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	ESLLoggerStartTime StartTime = ESLLoggerStartTime::AtBeginPlay;

	// Start after a given delay (if ESLLoggerStartTime::AfterDelay is selected)
	UPROPERTY(EditAnywhere, Category = "Semantic Logger"/*, meta = (editcondition = todo 4.22+)*/)
	float StartDelay = 0.5f;

	// Action name for starting from user input (if ESLLoggerStartTime::FromUserInput is selected)
	UPROPERTY(EditAnywhere, Category = "Semantic Logger"/*, meta = (editcondition = todo 4.22+)*/)
	FName UserInputActionName = TEXT("SLTrigger");
};

/* Holds the data needed to setup the world state logger */
USTRUCT()
struct FSLWorldStateLoggerParams
{
	GENERATED_BODY();

	// Update rate of the logger
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	float UpdateRate = 0.f;

	// Min difference between poses (FTransform) in order for the individual to be logged
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	float PoseTolerance = 0.5f;

	// Include individuals metadata 
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bIncludeMetadata = true;

	// Remove and overwrite any previously included metadata
	UPROPERTY(EditAnywhere, Category = "Semantic Logger", meta = (editcondition = "bIncludeMetadata"))
	bool bOverwriteMetadata = false;
};



/* Supported Events Struct*/
USTRUCT()
struct FLSymbolicEventsSelection
{
	GENERATED_BODY();

	/* All or selection */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events")
	bool bSelectAll = true;

	/* Contact */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bContact = true;

	/* Supported By */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bSupportedBy = true;

	/* Manipulator contact */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bManipulatorContact = true;

	/* Reach + PreGrasp */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bReachAndPreGrasp = true;

	/* Grasp */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bGrasp = true;

	/* PickAndPlace - Slide - PickUp - Transport - PutDown */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bPickAndPlace = true;

	///* Container */
	//UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	//bool bContainer = true;

	///* Slicing */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "!bSelectAll"))
	bool bSlicing = true;
};


/* Holds the types of events to be logged by the symbolic logger */
USTRUCT()
struct FSLSymbolicLoggerParams
{
	GENERATED_BODY();
	
	/* Events */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	FLSymbolicEventsSelection EventsSelection;

	/* Timelines */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bWriteTimelines = true;

	UPROPERTY(EditAnywhere, Category = "Semantic Logger|Events", meta = (editcondition = "bWriteTimelines"))
	FLSymbolicEventsSelection TimelineEventsSelection;

	/* ROS */
	UPROPERTY(EditAnywhere, Category = "Semantic Logger")
	bool bPublishToROS = false;
};
