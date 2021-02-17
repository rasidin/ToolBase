/***********************************************************
 ToolBase Source File
 -----------------------------------------------------------
 @file  TBApplication.cpp
 @brief ToolBase Application
 @author minseob (https://github.com/rasidin)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#include "TBApplication.h"
#include "TBCommon.h"
#include "TBWidget.h"
#include "TBTime.h"

#ifdef WIN32
#include <Windows.h>
#include <MMSystem.h>
#endif
#include <stdio.h>
#include <assert.h>

namespace ToolBase {
TBApplication* TBApplication::mInstance = 0;
TBApplication::TBApplication()
{
	assert(!mInstance);
	mInstance = static_cast<TBApplication*>(this);
}

TBApplication::~TBApplication()
{
	mInstance = 0;
}

int TBApplication::Run()
{
#ifdef WIN32
    WIDGETMESSAGE msg;
    while(1)
	{
		if (!TBWidget::GetCurrentWidgetNum()) break;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else {
			TBWidget::ForEachWidget([](TBWidget* widget, double deltaTime) {
				double time = TBTime::GetCurrentTimeSeconds();
				double widgetLastTime = widget->GetLastTimeSeconds();
				double elapsedTime = time - widgetLastTime;
				if (elapsedTime > widget->GetUpdateTimingSeconds()) {
					widget->FrameUpdate(elapsedTime);
					widget->SetLastTimeSeconds(time);
				}
			});
        }
	}
    return static_cast<int>(msg.wParam);
#else
    return 1;
#endif
}
}