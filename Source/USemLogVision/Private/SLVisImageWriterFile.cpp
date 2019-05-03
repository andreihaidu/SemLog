// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "SLVisImageWriterFile.h"
#include "FileHelper.h"

// Ctor
USLVisImageWriterFile::USLVisImageWriterFile()
{
	bIsInit = false;
}

// Dtor
USLVisImageWriterFile::~USLVisImageWriterFile()
{
}

// Init
void USLVisImageWriterFile::Init(const FSLVisImageWriterParams& InParams)
{
	// Set path to store the images
	DirPath = InParams.Location + InParams.EpisodeId + TEXT("_RP/");
	FPaths::RemoveDuplicateSlashes(DirPath);
	bIsInit = true;
}

// Finish
void USLVisImageWriterFile::Finish()
{
	if (bIsInit)
	{
		bIsInit = false;
	}
}

// Write the images at the timestamp
void USLVisImageWriterFile::Write(const FSLVisStampedData& StampedData)
{
	// Iterate the images from the current timestamp
	for (const auto& ViewData : StampedData.ViewsData)
	{
		// Iterate images from the view
		for (const auto& ImgData : ViewData.ImagesData)
		{
			FString Filename = FSLVisHelper::CreateImageFilename(StampedData.Timestamp, ViewData.Class, ImgData.RenderType);
			FString ImgPath = DirPath + "/" + Filename;
			FPaths::RemoveDuplicateSlashes(ImgPath);
			// Save to file
			FFileHelper::SaveArrayToFile(ImgData.BinaryData, *ImgPath);
		}
	}
}
