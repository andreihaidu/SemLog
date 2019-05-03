// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "SLVisRecordGameMode.h"
#include "SLVisLoggerSpectatorPC.h"

// Ctor
ASLVisRecordGameMode::ASLVisRecordGameMode()
{
	ReplaySpectatorPlayerControllerClass = ASLVisLoggerSpectatorPC::StaticClass();
}
