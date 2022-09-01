#pragma once

#include "ViewWidget.h"
#include "TwoeUnits.h"

#include "SGR/utils.h"

class MainViewWidget : public ViewWidget {
public:
	static MainViewWidget& get();

	void init(SGE* engine);
	void update() override;

	bool loadMolekule();

private:

	static MainViewWidget* singleton;
	MainViewWidget();
	~MainViewWidget() {;}

	const std::vector<SGEPosition> rectVertices{
		{-0.5f, -0.5f, 0.f},
		{ 0.5f, -0.5f, 0.f},
		{ 0.5f,  0.5f, 0.f},
		{-0.5f,  0.5f, 0.f}
	};

    const std::vector<uint16_t> rectIndices{0,1,2,2,3,0};
    Mesh rectangleMesh{"rectangle", rectVertices, rectIndices};

	std::string backgroundTexture;
	GameObject background{"Background", rectangleMesh, backgroundTexture};

	Molekule* _molekule;

	void addMolekuleToRender();
};