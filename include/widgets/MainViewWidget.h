#pragma once

#include "ViewWidget.h"
#include "TwoeUnits.h"
#include "MolekuleManager.h"

class MainViewWidget : public ViewWidget {
public:
	static MainViewWidget& get();

	void init(SGE* engine);
	void update() override;

	bool loadMolekule();

private:

	static MainViewWidget* singleton;
	MainViewWidget() {;}
	~MainViewWidget() {;}

	const std::vector<SGEPosition> rectVertices{
		{-0.5f, -0.5f, 0.f},
		{ 0.5f, -0.5f, 0.f},
		{ 0.5f,  0.5f, 0.f},
		{-0.5f,  0.5f, 0.f}
	};

    const std::vector<uint16_t> rectIndices{0,1,2,2,3,0};
    Mesh rectangleMesh{"rectangle", rectVertices, rectIndices};

	std::string backgroundTexture = "/Resources/Textures/back.jpg";
	GameObject background1{"Background1", rectangleMesh, backgroundTexture};
	GameObject background2{"Background2", rectangleMesh, backgroundTexture};
	GameObject background3{"Background3", rectangleMesh, backgroundTexture};
	GameObject background4{"Background4", rectangleMesh, backgroundTexture};
	GameObject background5{"Background5", rectangleMesh, backgroundTexture};

	MolekuleManager& molekuleManager = MolekuleManager::get();

	void addMolekuleToRender();
};