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
	static std::vector<CriticalPoint> _rcps;
	static std::vector<CriticalPoint> _ccps;

private:
	static void readMolekuleName(std::ifstream& inp);

	static void readAtoms(std::ifstream& inp);

	static void readCPT(std::ifstream& inp);

	static void readBonds(std::ifstream& inp, uint16_t num);
	static void readCCP(std::ifstream& inp, uint16_t num);
	static void readRCP(std::ifstream& inp, uint16_t num);
};