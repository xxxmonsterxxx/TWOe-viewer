#pragma once

#include <SGE.h>

#include "widgets/MainViewWidget.h"

class TwoeViewer {

public:
	static TwoeViewer& get();

	bool init();
	void deinit();
	void execute();

private:
	TwoeViewer() {;}
	~TwoeViewer() {;}

	static TwoeViewer* singleton;

	SGE& engine = SGE::get();

	MainViewWidget& mainWidget = MainViewWidget::get();
};