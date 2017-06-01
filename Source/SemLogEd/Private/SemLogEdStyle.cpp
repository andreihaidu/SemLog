// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "SemLogEdStyle.h"
#include "SemLogEdModule.h"
#include "SlateGameResources.h"
#include "IPluginManager.h"

#include "Styling/SlateTypes.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FSemLogEdStyle::StyleSetInstance = NULL;

void FSemLogEdStyle::Initialize()
{
	if (!StyleSetInstance.IsValid())
	{
		StyleSetInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSetInstance);
	}
};

void FSemLogEdStyle::Shutdown()
{
	if (StyleSetInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSetInstance);
		ensure(StyleSetInstance.IsUnique());
		StyleSetInstance.Reset();
	}
}

FName FSemLogEdStyle::GetStyleSetName()
{
	static FName SemLogStyleName(TEXT("SemLogEdStyle"));
	return SemLogStyleName;
}

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FSemLogEdStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("USemLog"))->GetContentDir());

	Style->Set("LevelEditor.SemLogEd", new IMAGE_BRUSH(TEXT("Icons/icon_Mode_SemLog_40px"), Icon40x40));
	Style->Set("LevelEditor.SemLogEd.Small", new IMAGE_BRUSH(TEXT("Icons/icon_Mode_SemLog_40px"), Icon20x20));

	return Style;
}

#undef IMAGE_BRUSH

void FSemLogEdStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSemLogEdStyle::Get()
{
	return *StyleSetInstance;
}