#include "widgets/MainViewWidget.h"
#include "DataLoader.h"

MainViewWidget* MainViewWidget::singleton = nullptr;

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
	// _engine->addToRender(background);

	Unit::initUnitGeometry();
}

bool MainViewWidget::loadMolekule()
{
	std::string wfnPath = getExecutablePath() + "/Resources/Test data/test.wfn";
	std::string cptPath = getExecutablePath() + "/Resources/Test data/test.cpt";

	DataLoader::loadData(wfnPath, cptPath);

	if (DataLoader::_atoms.empty() || DataLoader::_links.empty())
		return false;

	_molekule = new Molekule(DataLoader::_atoms,DataLoader::_links);

	addMolekuleToRender();

	return true;
}

void MainViewWidget::addMolekuleToRender()
{
	for (size_t i = 0; i < _molekule->_gameObjects.size(); i++) {
		_engine->addToRender(_molekule->_gameObjects[i]);
	}
}

void MainViewWidget::update()
{
}