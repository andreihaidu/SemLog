// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once
//#include "SemLogEdModule.h"
#include "CoreMinimal.h"
#include "PlatformFilemanager.h"
#include "FileManager.h"
#include "FileHelper.h"

struct EdModeUtils
{
	// Create semantic logs directory
	static bool SetupLoggingDirectory(const FString& DirectoryName)
	{
		// Get platform file
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		// Create directory, return true if already exists
		return PlatformFile.CreateDirectory(*FPaths::GameDir().Append("/").Append(DirectoryName));
	}

	// Check if semantic map already exists
	static bool SemanticMapExists(const FString& Path)
	{
		return IFileManager::Get().FileExists(*Path);
	}

	// Delete semantic map
	static bool DeleteSemanticMap(const FString& Path)
	{
		return IFileManager::Get().Delete(*Path);
	}


	// Generate semantic map button callback
	static FReply GenerateSemanticMap()
	{
		UE_LOG(SemLogEd, Warning, TEXT("Game DIR: %s "), *FPaths::GameDir());

		// Let editor know that we're about to do something that we want to undo/redo
		//GEditor->BeginTransaction(LOCTEXT("SemLogGenSemMap", "Generate Semantic Map"));

		// Get editor world
		UWorld* EdWorld = GEditor->GetEditorWorldContext().World();

		// Iterate all actor
		for (TActorIterator<AActor> ActorItr(EdWorld); ActorItr; ++ActorItr)
		{
			// Flag checking if the actor has a semantic logger tag set
			bool bHasSemLogTag = false;

			// Iterate all the tags, check for keyword "SemLog:"
			for (const auto& TagItr : ActorItr->Tags)
			{
				// Copy of the current tag as FString, Tag ex: "SemLog:Class,Box;Runtime,Dynamic;Id,yg6D;"
				FString CurrTag = TagItr.ToString();

				// Check if tag is related to the semantic logger
				if (CurrTag.RemoveFromStart("SemLog:"))
				{
					// Tag state: "Class,Box;Runtime,Dynamic;Id,yg6D;"
					bHasSemLogTag = true;

					// Stop iteration if object is ignored
					if (CurrTag.Contains("IGNORE"))
					{
						UE_LOG(SemLogEd, Warning, TEXT("%s - IGNORED"), *ActorItr->GetName());
						break;
					}

					// Map to store the key value properties
					TMap<FString, FString> SemLogProperties;

					// Split on semicolon, Tag state "Class,Box" / "Runtime,Dynamic" / "Id,yg6D"
					FString CurrPair;
					while (CurrTag.Split(TEXT(";"), &CurrPair, &CurrTag))
					{
						// Split on comma, Tag state "Class" / "Box"
						FString CurrKey, CurrValue;
						if (CurrPair.Split(TEXT(","), &CurrKey, &CurrValue))
						{
							SemLogProperties.Add(CurrKey, CurrValue);
						}
					}

					// Output properties
					for (const auto & PropElem : SemLogProperties)
					{
						UE_LOG(SemLogEd, Display, TEXT("Key %s - %s"), *PropElem.Key, *PropElem.Value);
					}
				}
			}

			if (!bHasSemLogTag)
			{
				// Actor has no semantic logging related tag
				UE_LOG(SemLogEd, Error, TEXT("%s - NO SemLog TAG, added IGNORE TAG"), *ActorItr->GetName());
				ActorItr->Tags.Add(FName(TEXT("SemLog:IGNORE;")));
			}
		}
		
		// Close transaction
		//GEditor->EndTransaction();

		return FReply::Handled();
	}

	//static bool IsAnythingSelected()
	//{			
	//	return GEditor->GetSelectedActors()->Num() != 0;
	//}

	//static FReply OnShowAllObjectsTagsButtonClick()
	//{
	//	// Let editor know that we're about to do something that we want to undo/redo
	//	GEditor->BeginTransaction(LOCTEXT("ShowAllObjectsTransactionName", "ShowAllObjects"));

	//	// For each selected actor
	//	for (TActorIterator<AActor> ActorItr(GEditor->GetEditorWorldContext().World()); ActorItr; ++ActorItr)
	//	{
	//		// Register actor in opened transaction (undo/redo)
	//		ActorItr->Modify();
	//		// Draw debug
	//		ActorItr->DrawDebugComponents();
	//		// Debug msg
	//		UE_LOG(SemLogEd, Warning, TEXT("All objects: %s"), *ActorItr->GetName());
	//	}			

	//	// We're done moving actors so close transaction
	//	GEditor->EndTransaction();

	//	return FReply::Handled();
	//}

	//static FReply OnShowSelectedObjectsTagsButtonClick()
	//{
	//	USelection* SelectedActors = GEditor->GetSelectedActors();

	//	// Let editor know that we're about to do something that we want to undo/redo
	//	GEditor->BeginTransaction(LOCTEXT("ShowSelectedObjectsTransactionName", "ShowSelectedObjects"));

	//	// For each selected actor
	//	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	//	{
	//		if (AActor* LevelActor = Cast<AActor>(*Iter))
	//		{
	//			// Register actor in opened transaction (undo/redo)
	//			LevelActor->Modify();
	//			// Draw debug
	//			LevelActor->DrawDebugComponents();
	//			// Debug msg
	//			UE_LOG(SemLogEd, Warning, TEXT("Selected objects: %s"), *LevelActor->GetName());
	//		}
	//	}

	//	// We're done moving actors so close transaction
	//	GEditor->EndTransaction();

	//	return FReply::Handled();
	//}

	//static FText GetTagsText()
	//{
	//	return LOCTEXT("TagsText", "etc.etc.\netc.etc");
	//}
};