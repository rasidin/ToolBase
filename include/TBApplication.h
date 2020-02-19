/***********************************************************
 ToolBase Header File
 -----------------------------------------------------------
 @file  TBApplication.h
 @brief ToolBase Application
 @author minseob (rasidin1@hotmail.com)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#pragma once

namespace ToolBase {
class TBApplication
{
public:
	TBApplication();
	~TBApplication();

	int Run();

	static TBApplication* GetInstance()				{ return mInstance; }

private:
	static TBApplication		*mInstance;
};
} // namespace ToolBase
