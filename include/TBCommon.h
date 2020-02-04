/***********************************************************
 ToolBase Header File
 -----------------------------------------------------------
 @file  TBCommon.h
 @brief ToolBase Common Definition
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#ifndef _TBCOMMON_H_
#define _TBCOMMON_H_

#ifdef WIN32
#define WIDGETHANDLE HWND
#define WIDGETMESSAGE MSG
#define WIDGETINSTANCE HINSTANCE
#else
#define WIDGETHANDLE
#define WIDGETMESSAGE
#endif

#ifndef LONG_MAX
#define LONG_MAX 0x7fffffffffffffffll
#endif
#ifndef ULONG_MAX
#define ULONG_MAX 0xffffffffffffffffull
#endif

#endif // _TBCOMMON_H_