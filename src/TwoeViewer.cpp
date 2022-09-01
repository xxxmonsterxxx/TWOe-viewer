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

bool TwoeViewer::init()
{
	mainWidget.init(&engine);
	cameraView.init(&engine);

	engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, cameraView.moveCallback);
	engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, cameraView.moveCallback);

	engine.keyEventSubscribe(GLFW_KEY_SPACE, GLFW_RELEASE, cameraView.keyCallback);


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

	cameraView.move({0,0,-12});

	while(engine.drawNextFrame()) {
		cameraView.moveUpdate();
		mainWidget.update();
    }
}