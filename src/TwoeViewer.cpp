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

	engine.setViewTransition({0,0,-7},0,{0,1,0});

	while(engine.drawNextFrame()) {
		engine.setViewTransition({0,0,0},0.2,{0,1,0});
		mainWidget.update();
    }
}