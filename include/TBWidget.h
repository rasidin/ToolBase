/***********************************************************
 LIMITEngine Source File
 Copyright (C), LIMITGAME, 2012
 -----------------------------------------------------------
 @file  TBWidget.h
 @brief ToolBase Widget
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#ifndef _TBWIDGET_H_
#define _TBWIDGET_H_

#ifdef WIN32
#include <Windows.h>
#endif
#include <string>
#include <vector>
#include <list>

#include "TBCommon.h"
#include "TBMath.h"
#include "TBEvent.h"

namespace ToolBase
{
class TBWidget
{
public:
	static WIDGETINSTANCE instanceHandle;
	static unsigned int createCounter;

    enum WidgetCreationFlag
    {
        CF_NOCAPTION = 1<<0,        // Create window that has no caption
    };

public:
	TBWidget(const char *name, int width=-1, int height=-1, int flag=0);
	~TBWidget();

	WIDGETHANDLE GetHandle()							    { return mHandle; }

    TBRect GetWindowRect();

    void SetLastTimeSeconds(double t)						{ mLastTimeSeconds = t; }
    double GetLastTimeSeconds() const						{ return mLastTimeSeconds; }

    void SetUpdateTimingSeconds(double ut)					{ mUpdateTimingSeconds = ut; }
    double GetUpdateTimingSeconds() const					{ return mUpdateTimingSeconds; }

	virtual void FrameUpdate(double elapasedTime)	{ /* Do nothing */ }
    virtual void MouseEvent(const MouseEvent &event);
    virtual void ResizeEvent(const ResizeEvent &event);

    virtual void Move(int x, int y);

    void AddChild(TBWidget *w)								{ mChildren.push_back(w); }
    void RemoveChild(TBWidget *w);

    // Static functions
	static void CloseWidget(WIDGETHANDLE handle);
	static size_t GetCurrentWidgetNum()						{ return gWidgetList.size(); }
    static TBWidget* FindWidget(WIDGETHANDLE handle);
	static void ForEachWidget(void (f)(TBWidget*, double));

protected:
	typedef std::list<TBWidget*> WidgetList;
	static WidgetList	gWidgetList;

    int					mCreationFlag;
	typedef std::vector<TBWidget*> WidgetVector;
	WidgetVector		mChildren;

	std::string			mName;
	std::string			mClassName;

	WIDGETHANDLE		mHandle;
	WIDGETMESSAGE		mMessage;

    bool				mMovable;
	TBPoint				mMousePosPrev;

    double				mLastTimeSeconds;
    double				mUpdateTimingSeconds;
};
}

#endif