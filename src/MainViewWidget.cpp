#include "widgets/MainViewWidget.h"
#include "DataLoader.h"
#include "tinyfiledialogs.h"

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

	_engine->registerGameObject(background1);
	background1.scale(20);
	background1.move({0,0,10});
	background1.rotate({0,0,0},{1,0,0},-90);
	_engine->registerGameObject(background2);
	background2.scale(20);
	background2.move({0,0,10});
	background2.rotate({0,0,0},{1,0,0},90);
	_engine->registerGameObject(background3);
	background3.scale(20);
	background3.move({0,0,10});
	background3.rotate({0,0,0},{0,1,0},90);
	_engine->registerGameObject(background4);
	background4.scale(20);
	background4.move({0,0,10});
	background4.rotate({0,0,0},{0,1,0},-90);
	_engine->registerGameObject(background5);
	background5.scale(20);
	background5.move({0,0,10});

	molekuleManager.init();

	Unit::initUnitGeometry();
}

bool MainViewWidget::loadMolekule()
{
	std::string resourcesPath = _engine->getResourcesPath()+"/Test data/";
	const char *filters[2] = { "*.wfn" };
    const char *filePath = tinyfd_openFileDialog(
        "Choose molekule file",
        resourcesPath.c_str(),
        1,
        filters,
        "Molekule data files",
        0 
    );

	std::string wfnPath(filePath);
	std::string cptPath = wfnPath.substr(0, wfnPath.size() - 4) + ".cpt";

	DataLoader::loadData(wfnPath, cptPath);

	if (DataLoader::_atoms.empty() || DataLoader::_links.empty())
		return false;

	Molekule* molekule = new Molekule(DataLoader::_atoms,DataLoader::_links);
	molekule->setCritPoints(DataLoader::_ccps, DataLoader::_rcps, DataLoader::_bcps);

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