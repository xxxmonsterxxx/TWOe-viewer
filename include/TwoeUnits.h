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

	void setPosition(SGEPosition newPos) { _position = newPos; }
	SGEPosition getPosition() { return _position; }

protected:

	static uint16_t _number; //count of units
	uint16_t _num; // number of instance

	glm::vec3 _symAxis; // symetric axes
	SGEPosition _position;

	static Mesh* _sphereMesh;
	static Mesh* _cylindMesh;
};

class Atom : public Unit {
public:
	struct atomInfo {
		std::string name;
		glm::vec3 color;
		float radius;
	} _info;

	static Atom createNewAtomInstance(std::string name) {
		return Atom(name,_number++);
	}

	GameObject initGameObject() override {
		GameObject newGO("Atom" + _info.name + std::to_string(_num), *_sphereMesh);
		newGO.setPosition(_position);
		glm::vec3 scale = {_info.radius,_info.radius,_info.radius};
		newGO.setScale(scale*0.1f);
		newGO.setColor(_info.color);
		return newGO;
	}

	TextObject initLabel() {
		TextObject label(_info.name + std::to_string(_num));
		
		label.rotate({180,0,0});
		label.setPosition({_position.x,_position.y,_position.z+_info.radius*0.2f});
		return label;
	}

	Atom& operator= (const Atom& b) { this->findAtomInfo(b._info.name); return *this; }

private:

	Atom(std::string name, uint8_t num) {
		_num = num;
		findAtomInfo(name);
	}

	void findAtomInfo(std::string name) {
		for (size_t i = 0; i < atomInfos.size(); i++)
			if (name == atomInfos[i].name)
				_info = atomInfos[i];
	}

	static const std::vector<atomInfo> atomInfos;

};

class MolekularLink : public Unit {

public:
	MolekularLink& operator= (const MolekularLink& b) { this->_begin=b._begin; this->_end = b._end; return *this; }

	GameObject initGameObject() override;

	static MolekularLink createNewLinkInstance(SGEPosition begin, SGEPosition end) {
		return MolekularLink(begin, end, _number++);
	}

private:

	MolekularLink(SGEPosition begin, SGEPosition end, uint8_t num) { _begin = begin; _end = end; _num = num; }

	SGEPosition _begin;
	SGEPosition _end;
};


class Molekule {

public:
	Molekule() {;}
	Molekule(std::vector<Atom> atoms, std::vector<MolekularLink> links);

	std::vector<GameObject> _gameObjects;
	std::vector<TextObject> _labels;

	void rotate(float angleX, float angleY, float angleZ);
	void move(glm::vec3 deltaPos);

private:
	glm::vec3 rotation{0,0,0};

	std::vector<Atom> _atoms;
	std::vector<MolekularLink> _links;

	void initGameObjects();
};