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

	WIDGETHANDLE GetHandle()							    { return _handle; }

    TBRect GetWindowRect();

    void SetLastTime(unsigned long t)                       { _lastTime = t; }
    unsigned long GetLastTime() const                        { return _lastTime; }

    void SetUpdateTiming(unsigned int ut)                   { _updateTiming = ut; }
    unsigned int GetUpdateTiming() const                    { return _updateTiming; }

	virtual void FrameUpdate(unsigned long elapasedTime)    { /* Do nothing */ }
    virtual void MouseEvent(const MouseEvent &event);
    virtual void ResizeEvent(const ResizeEvent &event);

    virtual void Move(int x, int y);

    void AddChild(TBWidget *w)                              { _children.push_back(w); }
    void RemoveChild(TBWidget *w);

    // Static functions
	static void WidgetClosed(WIDGETHANDLE handle);
	static size_t GetCurrentWidgetNum()					    { return _widgets.size(); }
	static TBWidget* GetWidget(unsigned int num)		    { return _widgets[num]; }
    static TBWidget* GetWidget(WIDGETHANDLE handle);

protected:
	static std::vector<TBWidget *>	_widgets;

    int                             _creationFlag;
    typedef std::vector<TBWidget *> VectorWidget;
    VectorWidget                    _children;

	std::string						_name;
	std::string						_className;

	WIDGETHANDLE					_handle;
	WIDGETMESSAGE					_message;

    TBPoint                         _mousePosPrev;
    bool                            _movable;

    unsigned long                   _lastTime;
    unsigned int                    _updateTiming;
};
}

#endif