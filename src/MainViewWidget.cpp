#include "widgets/MainViewWidget.h"

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

	background.setScale(60);
	background.setPosition({0,0,-50});
	_engine->addToRender(background);

	Unit::initUnitGeometry();
}

bool MainViewWidget::loadMolekule()
{
	// here we create molekule
	std::string file = getExecutablePath() + "/Resources/input.txt";

	// if (!file.open())
	// 	return false;

	int atomsNum = 0;
	int linksNum = 0;

	// if (atomsNum == 0 || linksNum == 0)
	// 	return false;

	std::vector<Atom> atoms;
	for (int i = 0; i < atomsNum; i++) {
		std::string name;
		Atom atom = Atom::createNewAtomInstance(name);
		SGEPosition newPos;
		atom.setPosition(newPos);
		atoms.push_back(atom);
	}

	std::vector<MolekularLink> links;
	for (int i = 0; i < linksNum; i++) {
		glm::vec3 begin;
		glm::vec3 end;
		MolekularLink link = MolekularLink::createNewLinkInstance(begin,end);
		SGEPosition newPos;
		links.push_back(link);
	}

	_molekule = new Molekule(atoms,links);	

	addMolekuleToRender();

	return true;
}

void MainViewWidget::addMolekuleToRender()
{
	for (size_t i = 0; i < _molekule->_gameObjects.size(); i++)
		_engine->addToRender(_molekule->_gameObjects[i]);
}

void MainViewWidget::update()
{
}