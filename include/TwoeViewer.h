#pragma once

#include <SGE/SGE.h>

#include "widgets/MainViewWidget.h"
#include "CameraView.h"

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
	CameraView& cameraView = CameraView::get();
};