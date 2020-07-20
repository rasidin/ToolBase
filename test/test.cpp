#include <TBApplication.h>
#include <TBWidget.h>

class SimpleWindow : public ToolBase::TBWidget
{
public:
	SimpleWindow(const char *Title) : ToolBase::TBWidget(Title, 640, 480) {}
	
	virtual void FrameUpdate(double frameTime) override {
	}

    virtual void KeyboardEvent(const ToolBase::KeyboardEvent &event)
    {
        printf("%d\n", event.key);
    }
};

int main()
{
	ToolBase::TBApplication app;
	SimpleWindow window("Test");
	app.Run();
	window.~SimpleWindow();
}