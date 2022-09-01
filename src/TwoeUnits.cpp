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

void Unit::initUnitGeometry()
{
	static std::vector<SGEPosition> vertices;
	static std::vector<uint16_t>	indices;
	
	initVertexDataSphere(vertices, indices);
	_sphereMesh = new Mesh("Sphere", vertices, indices, true);

	vertices.clear();
	indices.clear();
	initVertexDataCylinder(vertices, indices);
	_cylindMesh = new Mesh("Cylinder", vertices, indices, true);
}

GameObject MolekularLink::initGameObject()
{
	GameObject newGO("Molekular link" + std::to_string(_num), *_cylindMesh);

	glm::vec3 b = {_begin.x,_begin.y,_begin.z};
	glm::vec3 e = {_end.x,_end.y,_end.z};
	glm::vec3 l = e - b;
	glm::vec3 direction = glm::normalize(l);
	glm::vec3 center = b + direction*(glm::length(l)*0.5f);

	newGO.setPosition({center.x,center.y,center.z});

	glm::vec3 axis = glm::cross(glm::vec3(1,0,0), l); // axis is perpendicular to ({1,0,0} and link vector)
	if (glm::length(axis) != 0) {
		newGO.setRotation(axis,glm::degrees(glm::acos(direction.x))); // direction.x is cos beetween {1,0,0} and link vector
	}

	newGO.setScale({2,0.05,0.05});
	newGO.setColor({0,0,1});
	return newGO;
}

void Molekule::initGameObjects()
{
	for (size_t i = 0; i < _atoms.size(); i++)
		_gameObjects.push_back(_atoms[i].initGameObject());

	for (size_t i = 0; i < _links.size(); i++)
		_gameObjects.push_back(_links[i].initGameObject());
}