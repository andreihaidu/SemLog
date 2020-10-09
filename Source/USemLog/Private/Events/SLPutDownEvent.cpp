// Copyright 2017-2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "Events/SLPutDownEvent.h"
#include "Individuals/Type/SLBaseIndividual.h"
#include "Owl/SLOwlExperimentStatics.h"

// Constructor with initialization
FSLPutDownEvent::FSLPutDownEvent(const FString& InId, const float InStart, const float InEnd, const uint64 InPairId,
	USLBaseIndividual* InManipulator, USLBaseIndividual* InIndividual) :
	ISLEvent(InId, InStart, InEnd), PairId(InPairId), Manipulator(InManipulator), Individual(InIndividual)
{
}

// Constructor initialization without end time
FSLPutDownEvent::FSLPutDownEvent(const FString& InId, const float InStart, const uint64 InPairId,
	USLBaseIndividual* InIndividual, USLBaseIndividual* InManipulator) :
	ISLEvent(InId, InStart), PairId(InPairId), Manipulator(InManipulator), Individual(InIndividual)
{
}

/* Begin ISLEvent interface */
// Get an owl representation of the event
FSLOwlNode FSLPutDownEvent::ToOwlNode() const
{
	// Create the Lift event node
	FSLOwlNode EventIndividual = FSLOwlExperimentStatics::CreateEventIndividual(
		"log", Id, "PutDownSituation");
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateStartTimeProperty("log", StartTime));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateEndTimeProperty("log", EndTime));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreatePerformedByProperty("log", Manipulator->GetIdValue()));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateObjectActedOnProperty("log", Individual->GetIdValue()));
	return EventIndividual;
}

// Add the owl representation of the event to the owl document
void FSLPutDownEvent::AddToOwlDoc(FSLOwlDoc* OutDoc)
{
	// Add timepoint individuals
	// We know that the document is of type FOwlExperiment,
	// we cannot use the safer dynamic_cast because RTTI is not enabled by default
	// if (FOwlEvents* EventsDoc = dynamic_cast<FOwlEvents*>(OutDoc))
	FSLOwlExperiment* EventsDoc = static_cast<FSLOwlExperiment*>(OutDoc);
	EventsDoc->AddTimepointIndividual(
		StartTime, FSLOwlExperimentStatics::CreateTimepointIndividual("log", StartTime));
	EventsDoc->AddTimepointIndividual(
		EndTime, FSLOwlExperimentStatics::CreateTimepointIndividual("log", EndTime));
	EventsDoc->AddObjectIndividual(Individual,
		FSLOwlExperimentStatics::CreateObjectIndividual("log", Individual->GetIdValue(), Manipulator->GetClassValue()));
	EventsDoc->AddObjectIndividual(Manipulator,
		FSLOwlExperimentStatics::CreateObjectIndividual("log", Manipulator->GetIdValue(), Manipulator->GetClassValue()));
	OutDoc->AddIndividual(ToOwlNode());
}

// Get event context data as string (ToString equivalent)
FString FSLPutDownEvent::Context() const
{
	return FString::Printf(TEXT("PutDown - %lld"), PairId);
}

// Get the tooltip data
FString FSLPutDownEvent::Tooltip() const
{
	return FString::Printf(TEXT("\'O1\',\'%s\',\'Id\',\'%s\',\'O2\',\'%s\',\'Id\',\'%s\',\'Id\',\'%s\'"),
		*Individual->GetClassValue(), *Individual->GetIdValue(), *Manipulator->GetClassValue(), *Manipulator->GetIdValue(), *Id);
}

// Get the data as string
FString FSLPutDownEvent::ToString() const
{
	return FString::Printf(TEXT("Individual:[%s] Manipulator:[%s] PairId:%lld"),
		*Individual->GetInfo(), *Manipulator->GetInfo(), PairId);
}
/* End ISLEvent interface */