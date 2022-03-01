#pragma once

#include <vector>
#include <SGE.h>
#include "glm/glm.hpp"

class Unit {

public:
	Unit() {;}

	void rotate(float angle);
	void rotate(float angle, glm::vec3 axis);

	static void initUnitGeometry();
	virtual GameObject initGameObject() = 0;

protected:
	glm::vec3 _symAxis; // symetric axes
	SGEPosition _position;

	static Mesh* _sphereMesh;
	static Mesh* _cylindMesh;
};

class Atom : Unit {
public:
	struct atomInfo {
		std::string name;
		glm::vec3 color;
		float radius;
	} _info;

	static Atom createNewAtomInstance(std::string name) {
		return Atom(name,_number++);
	}

	void setPosition(SGEPosition newPos) { _position = newPos; }

	GameObject initGameObject() override {
		GameObject newGO("Atom" + _info.name + std::to_string(_num), *_sphereMesh);
		_position.z = -15;
		newGO.setPosition(_position);
		newGO.setColor(_info.color);
		newGO.setScale(_info.radius);
		return newGO;
	}

	Atom& operator= (const Atom& b) { this->findAtomInfo(b._info.name); return *this; }

private:

	Atom(std::string name, uint8_t num) {
		_num = num;
		findAtomInfo(name);
	}

	static uint16_t _number; //count of atoms

	uint16_t _num; // number of atom

	void findAtomInfo(std::string name) {
		for (size_t i = 0; i < atomInfos.size(); i++)
			if (name == atomInfos[i].name)
				_info = atomInfos[i];
	}

	static const std::vector<atomInfo> atomInfos;

};

class MolekularLink : Unit {

public:
	MolekularLink& operator= (const MolekularLink& b) { this->_begin=b._begin; this->_end = b._end; return *this; }

	GameObject initGameObject() override {
		return GameObject("Molekular link" + std::to_string(_number), *_cylindMesh);
	}

	static MolekularLink createNewLinkInstance(glm::vec3 begin, glm::vec3 end) {
		_number++;
		return MolekularLink(begin, end);
	}

private:

	MolekularLink(glm::vec3 begin, glm::vec3 end) { _begin = begin; _end = end; }

	static uint16_t _number;

	glm::vec3 _begin;
	glm::vec3 _end;

};


class Molekule {

public:
	Molekule() {;}
	Molekule(std::vector<Atom> atoms, std::vector<MolekularLink> links) {
		_atoms = atoms;
		_links = links;

		initGameObjects();
	}

	std::vector<GameObject> _gameObjects;

private:
	std::vector<Atom> _atoms;
	std::vector<MolekularLink> _links;

	void initGameObjects();
};