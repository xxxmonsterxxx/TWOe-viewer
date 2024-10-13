#pragma once

#include <SGE.h>

#include "widgets/MainViewWidget.h"

class TwoeViewer {

public:
	static TwoeViewer& get();

	bool init();
	void deinit();
	void execute();

	static void keyCallback(int key, int scancode, int action, int mods);

private:
	TwoeViewer() {;}
	~TwoeViewer() {;}

	static TwoeViewer* singleton;

	bool _exit;

	SGE& engine = SGE::get();

	MainViewWidget& mainWidget = MainViewWidget::get();
};