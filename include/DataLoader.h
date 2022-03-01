#pragma once

#include <string>
#include <vector>
#include "TwoeUnits.h"

const int periodic[] = {
	1,  53,  255, 255, 255,
	2,  31,  217, 255, 255,
	3,  167, 204, 128, 255,
	4,  112, 194, 255, 0,
	5,  87,  255, 181, 181,
	6,  67,  110, 110, 110,
	7,  56,  48,  80,  248,
	8,  48,  255, 13,  13,
	9,  42,  144, 224, 80,
	10, 38,  179, 227, 245
};

struct atom
{
	float pos_x;
	float pos_y;
	float pos_z;
	int charge;
};

struct bond_cp
{
	float pos_x;
	float pos_y;
	float pos_z;
	int a_ind;
	int b_ind;
};

class DataLoader {
public:

	static void loadData(const std::string wfnPath, const std::string cptPath);

	static std::string _molekuleName;
	static std::vector<Atom> _atoms;

	// int numberOfBonds;
	// bond_cp *bonds;

	// int **map;

	// int nummberOfCCPs;
	// std::vector <glm::vec3> cage_cp;

	// int nummberOfRCPs;
	// std::vector <glm::vec3> ring_cp;

private:
	static void readMolekuleName(std::ifstream& inp);
};