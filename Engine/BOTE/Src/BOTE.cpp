#pragma once
#include "Precompiled.h"
#include "BOTE.h"

BOTE::App& BOTE::GameApp()
{
	static App sApp;
	return sApp;
}