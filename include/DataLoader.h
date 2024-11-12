#pragma once

#include <string>
#include <vector>
#include "TwoeUnits.h"

class DataLoader {
public:

	static void loadData(const std::string wfnPath, const std::string cptPath);

	static std::string _molekuleName;
	static std::vector<Atom> _atoms;
	static std::vector<MolekularLink> _links;

	// int numberOfBonds;
	// bond_cp *bonds;

	// int **map;

	// int nummberOfCCPs;
	// std::vector <glm::vec3> cage_cp;

	// int nummberOfRCPs;
	// std::vector <glm::vec3> ring_cp;

private:
	static void readMolekuleName(std::ifstream& inp);
	static void readAtoms(std::ifstream& inp);
	static void readBonds(std::ifstream& inp);
};