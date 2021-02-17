/***********************************************************
 ToolBase Source File
 -----------------------------------------------------------
 @file  TBMessageBox.cpp
 @brief ToolBase Mesage Box
 @author minseob (https://github.com/rasidin)
 -----------------------------------------------------------
 History:
 - 2012/5/9 Created by minseob
 ***********************************************************/

#ifdef WIN32
#include <Windows.h>
#endif

#include "TBMessageBox.h"

namespace ToolBase {
// -----------------------------------------------------------
// Static Functions
// -----------------------------------------------------------
void TBMessageBox::About(const char *message)
{
#ifdef WIN32
    ::MessageBox(0, message, "About", MB_OK);
#endif
}
}