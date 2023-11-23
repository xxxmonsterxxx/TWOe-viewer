#include "TwoeViewer.h"
#include "TwoeUnits.h"
#include <stdio.h>

TwoeViewer* TwoeViewer::singleton = nullptr;

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
	cameraView.init(&engine, {0,0,-12});

	// camera options
	// engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, cameraView.moveCallback);
	// engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, cameraView.moveCallback);
	// engine.keyEventSubscribe(GLFW_KEY_SPACE, GLFW_RELEASE, cameraView.keyCallback);

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
		cameraView.moveUpdate();
		mainWidget.update();
		engineWorks = engine.drawNextFrame();
    }
}