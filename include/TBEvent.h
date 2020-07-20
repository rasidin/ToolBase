/***********************************************************
 ToolBase Header File
 -----------------------------------------------------------
 @file  TBEvent.h
 @brief ToolBase Events
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2013/7/20 Created by minseob
 ***********************************************************/

#ifndef _TBEVENT_H_
#define _TBEVENT_H_

namespace ToolBase {
    typedef struct _MouseEvent 
    {
        enum BUTTON { BUTTON_NONE = 0, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_CENTER };
        enum STATUS { STATUS_DOWN, STATUS_UP, STATUS_MOVE };
        
        struct { int x, y; }    pos;
        BUTTON                  button;
        STATUS                  status;
        _MouseEvent() { pos.x = 0; pos.y = 0; }
        _MouseEvent(int x, int y, BUTTON btn, STATUS sta) { pos.x = x; pos.y = y; button = btn; status = sta; }
    } MouseEvent;
    typedef struct _ResizeEvent
    {
        struct { int width, height; }     size;
        _ResizeEvent() { size.width = 0; size.height = 0; }
        _ResizeEvent(int width, int height) { size.width = width, size.height = height; }
    } ResizeEvent;
    typedef struct _KeyboardEvent
    {
        enum STATUS { STATUS_DOWN, STATUS_UP } status;
        unsigned int key;
        _KeyboardEvent(STATUS inStatus, unsigned int inKey) : status(inStatus), key(inKey) {}
    } KeyboardEvent;
}

#endif