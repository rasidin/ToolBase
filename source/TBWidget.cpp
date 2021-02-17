/***********************************************************
 ToolBase Source File
 -----------------------------------------------------------
 @file  TBWidget.cpp
 @brief ToolBase Message Box
 @author minseob (https://github.com/rasidin)
 -----------------------------------------------------------
 History:
 - 2012/6/14 Created by minseob
 ***********************************************************/
#include "TBWidget.h"

#include "TBCommon.h"
#include "TBApplication.h"
#include "TBTime.h"

namespace ToolBase {
WIDGETINSTANCE TBWidget::instanceHandle = 0;
unsigned int TBWidget::createCounter = 0;
std::list<TBWidget*> TBWidget::gWidgetList;
#ifdef WIN32
LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		TBWidget::CloseWidget(hWnd);
		break;
    case WM_SIZE:
    case WM_SIZING:
        if (TBWidget *widget = TBWidget::FindWidget(hWnd))
        {
            ResizeEvent re;
            re.size.width = LOWORD(lParam);
            re.size.height = HIWORD(lParam);
            widget->ResizeEvent(re);
        }
        break;
    case WM_KEYDOWN:
        if (TBWidget *widget = TBWidget::FindWidget(hWnd))
        {
            widget->KeyboardEvent(KeyboardEvent(KeyboardEvent::STATUS_DOWN, static_cast<unsigned int>(wParam)));
        } break;
    case WM_KEYUP:
        if (TBWidget *widget = TBWidget::FindWidget(hWnd))
        {
            widget->KeyboardEvent(KeyboardEvent(KeyboardEvent::STATUS_UP, static_cast<unsigned int>(wParam)));
        } break;
    case WM_MOUSEMOVE:
        if (TBWidget *widget = TBWidget::FindWidget(hWnd))
        {
            MouseEvent me;
            me.pos.x = LOWORD(lParam);
            me.pos.y = HIWORD(lParam);
            me.status = MouseEvent::STATUS_MOVE;
            if (wParam & MK_LBUTTON) me.button = MouseEvent::BUTTON_LEFT;
            if (wParam & MK_RBUTTON) me.button = MouseEvent::BUTTON_RIGHT;
            widget->MouseEvent(me);
        } break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
        if (TBWidget *widget = TBWidget::FindWidget(hWnd))
        {
            MouseEvent me;
            me.pos.x = LOWORD(lParam);
            me.pos.y = HIWORD(lParam);
            switch(Msg)
            {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
                me.status = MouseEvent::STATUS_DOWN;
                break;
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
                me.status = MouseEvent::STATUS_UP;
                break;
            }
            switch(Msg)
            {
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
                me.button = MouseEvent::BUTTON_LEFT;
                break;
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
                me.button = MouseEvent::BUTTON_RIGHT;
                break;
            }
            widget->MouseEvent(me);
        }
        break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}
#endif
void TBWidget::ForEachWidget(void (f)(TBWidget*, double)) 
{
	float deltaTime = 0.0;
	for (WidgetList::iterator wlit = gWidgetList.begin(); wlit != gWidgetList.end(); wlit++) {
		f(*wlit, deltaTime);
	}
}
TBWidget::TBWidget(const char *name, int width, int height, int flag)
	: mCreationFlag(flag)
	, mName(name)
	, mClassName("TBWidget")
	, mHandle(NULL)
	, mMessage()
    , mMovable(false)
    , mLastTimeSeconds(TBTime::GetCurrentTimeSeconds())
    , mUpdateTimingSeconds(0.016)     // 16ms (60fps)
{
#ifdef WIN32
	mClassName = "TBWidget";
	mClassName += createCounter;

	WNDCLASSEX	wcex;
	wcex.cbSize			= sizeof(wcex);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WinProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.lpszClassName	= mClassName.c_str();
	wcex.hInstance		= instanceHandle;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.hIconSm		= NULL;

	if (!RegisterClassEx(&wcex))
	{
		return;
	}

    if (width < 0 || height < 0)
    {
        width = 400;
        height = 300;
    }

    DWORD dwExStyle = WS_EX_WINDOWEDGE;
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;

    if (flag & CF_NOCAPTION) {
        dwExStyle = WS_EX_WINDOWEDGE & (~WS_CAPTION);
        dwStyle = WS_POPUP;
    }

	mHandle = CreateWindowEx(
		dwExStyle,
		mClassName.c_str(),
		mName.c_str(),
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		instanceHandle,
		NULL );

	ShowWindow(mHandle, SW_SHOWDEFAULT);
	UpdateWindow(mHandle);

	createCounter++;
	gWidgetList.push_back(this);
#endif
}

TBWidget::~TBWidget()
{
	UnregisterClass(mClassName.c_str(), instanceHandle);
}

void
TBWidget::RemoveChild(TBWidget *w)
{
    for(WidgetVector::iterator tbwit = mChildren.begin();tbwit != mChildren.end();tbwit++)
    {
        if (*tbwit == w)
        {
            mChildren.erase(tbwit);
            break;
        }
    }
}

TBRect
TBWidget::GetWindowRect()
{
    RECT rect;
    ::GetWindowRect(mHandle, &rect);
    return TBRect(rect.top, rect.bottom, rect.left, rect.right);
}

void
TBWidget::MouseEvent(const _MouseEvent &event)
{
    if (event.button == MouseEvent::BUTTON_LEFT)
    {
        if (event.status == MouseEvent::STATUS_DOWN)
        {
			mMousePosPrev = TBPoint(event.pos.x, event.pos.y);
            TBRect rect = this->GetWindowRect();
        }
        if (event.status == MouseEvent::STATUS_MOVE)
        {
            if (mMovable) {
                TBPoint moved(event.pos.x - mMousePosPrev.x, event.pos.y - mMousePosPrev.y);
                TBRect rect = this->GetWindowRect();
                Move(rect.left + moved.x, rect.top + moved.y);
            }
        }
    }
}

void
TBWidget::ResizeEvent(const _ResizeEvent &event)
{
    for(WidgetVector::iterator tbwit = mChildren.begin();tbwit != mChildren.end();tbwit++)
    {
        (*tbwit)->ResizeEvent(event);
    }
}

void 
TBWidget::CloseWidget(WIDGETHANDLE handle)
{
	for(WidgetList::iterator wlit = gWidgetList.begin();wlit != gWidgetList.end();++wlit)
	{
		if ((*wlit)->GetHandle() ==  handle)
		{
			gWidgetList.erase(wlit);
			break;
		}
	}
}

TBWidget* 
TBWidget::FindWidget(WIDGETHANDLE handle)
{
	for(WidgetList::iterator wlit = gWidgetList.begin();wlit != gWidgetList.end();++wlit)
    {
        if ((*wlit)->GetHandle() == handle)
        {
			return *wlit;
        }
    }
    return NULL;
}

void
TBWidget::Move(int x, int y)
{
    TBRect rect = this->GetWindowRect();
    MoveWindow(mHandle, x, y, rect.width(), rect.height(), true);
}
}