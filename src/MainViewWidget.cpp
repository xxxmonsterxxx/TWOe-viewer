#include "widgets/MainViewWidget.h"
#include "DataLoader.h"

MainViewWidget* MainViewWidget::singleton = nullptr;

MainViewWidget::MainViewWidget()
{
	backgroundTexture = _engine->getExecPath() + "/Resources/Textures/glass.jpeg";
}

MainViewWidget& MainViewWidget::get()
{
	if (!singleton) {
		singleton = new MainViewWidget();
		return *singleton;
	}
	return *singleton;
}

void MainViewWidget::init(SGE* engine)
{
	name = "Main widget";
	_engine = engine;

	background.setScale({60,60,60});
	background.setPosition({0,0,-50});
	//_engine->registerGameObject(background);
	_engine->setViewTransition({0,0,-15});

	molekuleManager.init();

	Unit::initUnitGeometry();
}

bool MainViewWidget::loadMolekule()
{
	std::string wfnPath = _engine->getExecPath() + "/Resources/Test data/test2.wfn";
	std::string cptPath = _engine->getExecPath() + "/Resources/Test data/test2.cpt";

	DataLoader::loadData(wfnPath, cptPath);

	if (DataLoader::_atoms.empty() || DataLoader::_links.empty())
		return false;

	Molekule* molekule = new Molekule(DataLoader::_atoms,DataLoader::_links);

	molekuleManager.setLoadedMolekule(molekule);

	addMolekuleToRender();

	return true;
}

void MainViewWidget::addMolekuleToRender()
{
	Molekule* molekuleToDraw = molekuleManager.getLoadedMolekule();

	for (size_t i = 0; i < molekuleToDraw->_gameObjects.size(); i++) {
		_engine->registerGameObject(molekuleToDraw->_gameObjects[i]);
	}

	for (size_t i = 0; i < molekuleToDraw->_labels.size(); i++) {
		_engine->registerGameObject(molekuleToDraw->_labels[i]);
	}
}

void MainViewWidget::update()
{
	molekuleManager.update();
}