// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "EngineMinimal.h"
#include "SLOwlExperiment.h"

/**
* Helper functions for generating owl experiment documents
*/
struct USEMLOGOWL_API FSLOwlExperimentStatics
{
	/* Events doc (experiment) template creation */
	// Create Default experiment
	static TSharedPtr<FSLOwlExperiment> CreateDefaultExperiment(
		const FString& InDocId,
		const FString& InDocPrefix = "log",
		const FString& InDocOntologyName = "Experiment");

	// Create UE experiment
	static TSharedPtr<FSLOwlExperiment> CreateUEExperiment(
		const FString& InDocId,
		const FString& InDocPrefix = "log",
		const FString& InDocOntologyName = "UE-Experiment");
		
		
	/* Owl individuals / definitions creation */
	// Create an event individual
	static FSLOwlNode CreateEventIndividual(
		const FString& InDocPrefix, 
		const FString& InId,
		const FString& InClass);

	// Create a timepoint individual
	static FSLOwlNode CreateTimepointIndividual(
		const FString& InDocPrefix,
		const float Timepoint);

	// Create an object individual
	static FSLOwlNode CreateObjectIndividual(
		const FString& InDocPrefix,
		const FString& InId,
		const FString& InClass);


	/* Owl properties creation */
	// Create class property
	static FSLOwlNode CreateClassProperty(const FString& InClass);

	// Create startTime property
	static FSLOwlNode CreateStartTimeProperty(
		const FString& InDocPrefix, const float Timepoint);

	// Create endTime property
	static FSLOwlNode CreateEndTimeProperty(
		const FString& InDocPrefix, const float Timepoint);

	// Create inContact property
	static FSLOwlNode CreateInContactProperty(
		const FString& InDocPrefix, const FString& InObjId);

	// Create isSupported property
	static FSLOwlNode CreateIsSupportedProperty(
		const FString& InDocPrefix, const FString& InObjId);

	// Create supports property
	static FSLOwlNode CreateIsSupportingProperty(
		const FString& InDocPrefix, const FString& InObjId);
	
	// Create performedBy property
	static FSLOwlNode CreatePerformedByProperty(
		const FString& InDocPrefix, const FString& InObjId);

	// Create deviceUsed property
	static FSLOwlNode CreateDeviceUsedProperty(
		const FString& InDocPrefix, const FString& InObjId);

	// Create objectActedOn property
	static FSLOwlNode CreateObjectActedOnProperty(const FString& InDocPrefix, const FString& InObjId);

	// Create outputsCreated property
	static FSLOwlNode CreateOutputsCreatedProperty(const FString& InDocPrefix, const FString& InObjId);

	// Create TaskSuccess property
	static FSLOwlNode CreateTaskSuccessProperty(const FString& InDocPrefix, const bool TaskSuccess);
};
