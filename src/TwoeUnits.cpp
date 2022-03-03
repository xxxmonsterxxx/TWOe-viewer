#include "TwoeUnits.h"
#include "geometry/sphere.h"
#include "geometry/cylinder.h"

const std::vector<Atom::atomInfo> Atom::atomInfos = {	
														{ "H", {  0,  0,  1},  1},
														{ "O", {  1,  0,  0},  8},
														{ "C", {  0,  1,  0},  6},
													  	{"Cl", {  0,  1,  0}, 17},
														{" N", {  0,  0,  1},  7}
																					};


Mesh* Unit::_sphereMesh = nullptr;
Mesh* Unit::_cylindMesh = nullptr;
uint16_t Atom::_number = 0;
uint16_t MolekularLink::_number = 0;

void Unit::initUnitGeometry()
{
	static std::vector<SGEPosition> vertices;
	static std::vector<uint16_t>	indices;
	
	initVertexDataSphere(vertices, indices);
	_sphereMesh = new Mesh("Sphere", vertices, indices, false);

	initVertexDataCylinder(vertices, indices);
	_cylindMesh = new Mesh("Cylinder", vertices, indices, false);
}

void Molekule::initGameObjects()
{
	for (size_t i = 0; i < _atoms.size(); i++)
		_gameObjects.push_back(_atoms[i].initGameObject());

	for (size_t i = 0; i < _links.size(); i++)
		_gameObjects.push_back(_links[i].initGameObject());
}