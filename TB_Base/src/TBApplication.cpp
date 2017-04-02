/***********************************************************
 ToolBase Source File
 -----------------------------------------------------------
 @file  TBApplication.cpp
 @brief ToolBase Application
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#include "TBApplication.h"
#include "TBCommon.h"
#include "TBWidget.h"

#ifdef WIN32
#include <Windows.h>
#include <MMSystem.h>
#endif
#include <stdio.h>
#include <assert.h>

namespace ToolBase {
TBApplication* TBApplication::_instance = 0;
TBApplication::TBApplication()
	: _quit(false)
{
	assert(!_instance);
	_instance = static_cast<TBApplication*>(this);
}

TBApplication::~TBApplication()
{
	_instance = 0;
}

int TBApplication::Run()
{
	while(1)
	{
#ifdef WIN32
        unsigned long time = timeGetTime();
        WIDGETMESSAGE msg;
        if (!TBWidget::GetCurrentWidgetNum()) break;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
            if (!GetMessage(&msg, NULL, 0, 0))
                return static_cast<int>(msg.wParam);

            TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else {
            for (unsigned int wgidx = 0; wgidx < TBWidget::GetCurrentWidgetNum(); wgidx++)
            {
                TBWidget *widget = TBWidget::GetWidget(wgidx);
                unsigned long widgetLastTime = widget->GetLastTime();
                unsigned long elapsedTime = 0UL;
                if (widgetLastTime > time) {
                    elapsedTime = ULONG_MAX - widgetLastTime + time;
                }
                else {
                    elapsedTime = time - widgetLastTime;
                }
                if (elapsedTime > widget->GetUpdateTiming()) {
                    widget->FrameUpdate(elapsedTime);
                    widget->SetLastTime(time);
                }
            }
        }
        Sleep(1);
#endif
	}
	return 1;
}
}