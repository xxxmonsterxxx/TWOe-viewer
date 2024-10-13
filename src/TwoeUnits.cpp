#include "TwoeUnits.h"
#include "geometry/sphere.h"
#include "geometry/cylinder.h"

const std::vector<Atom::atomInfo> Atom::atomInfos = {	
														{ "H", {  1.00, 1.00, 1.00},  1},
														{ "O", {  1.00, 0.04, 0.04},  8},
														{ "C", {  0.30, 0.30, 0.30},  2.5},
													  	{"Cl", {  0.04, 1.00, 0.20},  4},
														{ "N", {  0.04, 0.10, 1.00},  7},
														{"He", {  0.00, 1.00, 1.00},  1.5},
																							};


Mesh* Unit::_sphereMesh = nullptr;
Mesh* Unit::_cylindMesh = nullptr;
uint16_t Unit::_number = 0;

Molekule::Molekule(std::vector<Atom> atoms, std::vector<MolekularLink> links) {
	_atoms = atoms;
	_links = links;

	initGameObjects();
}

void Unit::initUnitGeometry()
{
	static std::vector<SGEPosition> vertices;
	static std::vector<uint16_t>	indices;
	
	initVertexDataSphere(vertices, indices);
	_sphereMesh = new Mesh("Sphere", vertices, indices, false);

	vertices.clear();
	indices.clear();
	initVertexDataCylinder(vertices, indices);
	_cylindMesh = new Mesh("Cylinder", vertices, indices, false);
}

GameObject MolekularLink::initGameObject()
{
	GameObject newGO("Molekular link" + std::to_string(_num), *_cylindMesh);

	glm::vec3 b = {_begin.x,_begin.y,_begin.z};
	glm::vec3 e = {_end.x,_end.y,_end.z};
	glm::vec3 l = e - b;
	glm::vec3 direction = glm::normalize(l);
	glm::vec3 center = b + direction*(glm::length(l)*0.5f);

	newGO.setPosition(center);

	glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(1,0,0), l)); // axis is perpendicular to ({1,0,0} and link vector)
	float angle = glm::degrees(glm::acos(direction.x)); // direction.x is cos beetween {1,0,0} and link vector
	if (glm::length(axis) != 0) {
		newGO.rotate(center, center+axis, angle);
	}

	newGO.setScale({glm::length(l),0.05,0.05});
	newGO.setColor({0,0,1});
	return newGO;
}

void Molekule::initGameObjects()
{
	for (size_t i = 0; i < _atoms.size(); i++) {
		_gameObjects.push_back(_atoms[i].initGameObject());
		_labels.push_back(_atoms[i].initLabel());
	}

	for (size_t i = 0; i < _links.size(); i++)
		_gameObjects.push_back(_links[i].initGameObject());
}

void Molekule::rotate(float angleX, float angleY, float angleZ)
{
	rotation+=glm::vec3{angleX,angleY,angleZ};

	for (size_t i = 0; i < _gameObjects.size(); i++)
		_gameObjects[i].rotate({0,0,0},{1,0,0},angleX);

	for (size_t i = 0; i < _gameObjects.size(); i++)
		_gameObjects[i].rotate({0,0,0},{0,1,0},angleY);

	for (size_t i = 0; i < _labels.size(); i++) {
		_labels[i].rotate({0,0,0},{1,0,0},angleX);
		_labels[i].setRotation({180,0,0});
	}

	for (size_t i = 0; i < _labels.size(); i++) {
		_labels[i].rotate({0,0,0},{0,1,0},angleY);
		_labels[i].setRotation({180,0,0});
	}
}

void Molekule::move(glm::vec3 deltaPos)
{
	for (size_t i = 0; i < _gameObjects.size(); i++)
		_gameObjects[i].move(deltaPos);

	for (size_t i = 0; i < _labels.size(); i++) {
		_labels[i].move(deltaPos);
	}
}