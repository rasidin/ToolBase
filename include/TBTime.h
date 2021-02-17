/***********************************************************
 ToolBase Header File
 -----------------------------------------------------------
 @file  TBTime.h
 @brief Time for ToolBase
 @author minseob (https://github.com/rasidin)
 ***********************************************************/
#pragma once
#include <windows.h>

namespace ToolBase {
	class TBTime {
	public:
		static inline double GetCurrentTimeSeconds() {
			LARGE_INTEGER Frequency;
			QueryPerformanceFrequency(&Frequency);
			LARGE_INTEGER Cycles;
			QueryPerformanceCounter(&Cycles);

			return (double)Cycles.QuadPart / (double)Frequency.QuadPart;
		}
	};
}