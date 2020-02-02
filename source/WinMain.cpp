/***********************************************************
 ToolBase Source File
 -----------------------------------------------------------
 @file  WinMain.cpp
 @brief WinMain
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/5/8 Created by minseob
 ***********************************************************/

#ifdef WIN32

#include <windows.h>
#include <string.h>

#include "TBCommon.h"
#include "TBWidget.h"

extern int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ToolBase::TBWidget::instanceHandle = hInstance;
	return main();
}

#endif // WIN32