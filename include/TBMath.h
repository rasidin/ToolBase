/***********************************************************
ToolBase Header File
-----------------------------------------------------------
@file  TBMath.h
@brief ToolBase Math Functions
@author minseob (https://github.com/rasidin)
-----------------------------------------------------------
History:
- 2014/1/24 Created by minseob
***********************************************************/
#ifndef _TBMATH_H_
#define _TBMATH_H_

namespace ToolBase {
	class TBRect
	{
	public:
		int left, right, top, bottom;
	public:
		TBRect() : left(0), right(0), top(0), bottom(0) {}
		TBRect(int l, int r, int t, int b)
			: left(l), right(r), top(t), bottom(b) {}

		int width() { return right - left; }
		int height() { return bottom - top;  }
	};/*TBRect*/
	class TBPoint
	{
	public:
		int x, y;
	public:
		TBPoint() : x(0), y(0) {}
		TBPoint(int x_, int y_) : x(x_), y(y_) {}
	};
}/*namespace ToolBase*/

#endif