#include "TwoeViewer.h"
#include "TwoeUnits.h"
#include <stdio.h>

TwoeViewer* TwoeViewer::singleton = nullptr;

TwoeViewer::TwoeViewer()
{
#if __APPLE__ && !NDBUG
	engine.setResourcesPath(SGE::getExecPath()+"/../Resources");
#else
	engine.setResourcesPath(SGE::getExecPath()+"/Resources");
#endif
}

TwoeViewer& TwoeViewer::get()
{
	if (!singleton) {
		singleton = new TwoeViewer();
		return *singleton;
	}

	return *singleton;
}

void TwoeViewer::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) {
		if (action == GLFW_RELEASE) {
			get()._exit = true;
		}
	}
}

bool TwoeViewer::init()
{
	mainWidget.init(&engine);

	engine.setMaxInstanceNumber(500);
	engine.keyEventSubscribe(GLFW_KEY_ESCAPE, GLFW_RELEASE, keyCallback);

	_exit = false;

	return true;
}

void TwoeViewer::deinit()
{
	
}

void TwoeViewer::execute()
{
	if (!mainWidget.loadMolekule())
		return;
		
	if (!mainWidget.show())
		return;

	if (!engine.init(800,800,"TWOe-Viewer")) // SGE init
		return;

	bool engineWorks = engine.drawNextFrame();
	while(engineWorks && !_exit) {
		mainWidget.update();
		engineWorks = engine.drawNextFrame();
    }
}