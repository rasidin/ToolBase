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
#ifndef _TBAPPLICATION_H_
#define _TBAPPLICATION_H_

namespace ToolBase {
class TBApplication
{
public:
	TBApplication();
	~TBApplication();

	int Run();
	void ReadyToQuit()								{ _quit = true; }

	static TBApplication* GetInstance()				{ return _instance; }

private:
	static TBApplication		*_instance;

	bool						 _quit;
};
} // namespace ToolBase

#endif // _TBAPPLICATION_H_