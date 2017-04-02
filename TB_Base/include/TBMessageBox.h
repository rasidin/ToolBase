/***********************************************************
 ToolBase Header File
 -----------------------------------------------------------
 @file  TBMessageBox.h
 @brief ToolBase Mesage Box
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/5/9 Created by minseob
 ***********************************************************/

#ifndef _TBMESSAGEBOX_H_
#define _TBMESSAGEBOX_H_

namespace ToolBase {
class TBMessageBox
{
public:             // Public Functions
    // ----------------------------------------------
    // Ctor & Dtor
    // ----------------------------------------------
    TBMessageBox()      {}
    ~TBMessageBox()     {}

    // ----------------------------------------------
    // Static Functions
    // ----------------------------------------------
    static void About(const char *message);
};
}

#endif // _TBMESSAGEBOX_H_