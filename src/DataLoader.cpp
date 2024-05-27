#include "DataLoader.h"
#include <stdio.h>
#include <iostream>

std::string DataLoader::_molekuleName;
std::vector<Atom> DataLoader::_atoms;
std::vector<MolekularLink> DataLoader::_links;

void DataLoader::readMolekuleName(std::ifstream& inp)
{
	std::string tmp;
	std::getline(inp, tmp);

	for (size_t i = 0; i < tmp.length(); i++) {
		if (tmp[i] == ' ' && i != 0) {
			char buffer[20];
			tmp.copy(buffer,(i-1),1);
			buffer[i-1]='\0';
			_molekuleName = buffer;
			std::cout<<"Found molekule --- "<<_molekuleName.c_str()<<" --- ";
			break;
		}
	}

	std::cout<<"\nStart molekule parse";

	int idxOfStartAtomName = 0;
	for (size_t i = 0; i < _molekuleName.length(); i++) {
		if (idxOfStartAtomName == -1) { // if start atom name not found
			if (!std::isdigit(_molekuleName[i]) && std::isdigit(_molekuleName[i-1])) { //start of atom name
				idxOfStartAtomName = i;
			}
		}

		if (std::isdigit(_molekuleName[i]) && !std::isdigit(_molekuleName[i-1])) { //end of atom name
			char atomName[3];
			_molekuleName.copy(atomName, (i-idxOfStartAtomName), idxOfStartAtomName);
			atomName[(i-idxOfStartAtomName)]='\0';
			idxOfStartAtomName = -1;
			std::cout<<"\nAtom "<<atomName;
			for (size_t j = i; j < _molekuleName.length()+1; j++) {
				if (!std::isdigit(_molekuleName[j]) && std::isdigit(_molekuleName[j-1])) { //end of atom count
					char atomCount[3];
					_molekuleName.copy(atomCount, (j-i), i);
					atomCount[(j-i)]='\0';
					std::cout<<" count = "<< atoi(atomCount);
					for (size_t k = 0; k < atoi(atomCount); k++)
						_atoms.push_back(Atom::createNewAtomInstance(atomName));
					break;
				}
			}
		}
	}
}

void DataLoader::readAtoms(std::ifstream& inp)
{
	std::string tmp;
	std::getline(inp, tmp);
	int numberOfAtoms;

	inp >> tmp >> numberOfAtoms	>> tmp >> tmp >> numberOfAtoms >> tmp >> numberOfAtoms >> tmp;

	for (int i = 0; i < numberOfAtoms; i++)
	{
		getline(inp, tmp);
		float x,y,z,charge;
		inp >> tmp;
		Atom newAtom = Atom::createNewAtomInstance(tmp);
		inp >> tmp >> tmp >> tmp >> x >> y >> z >> tmp >> tmp >> charge;
		newAtom.setPosition({x,y,z});
		_atoms.push_back(newAtom);
	}
}

void DataLoader::readBonds(std::ifstream& inp)
{
	uint16_t numOfBonds;
	std::string tmp;

	while (tmp != "BCPs")
	{
		getline(inp, tmp);
		inp >> tmp >> tmp;
	}
	inp >> tmp >> numOfBonds;

	getline(inp, tmp);
	inp >> tmp >> tmp >> tmp >> tmp;
	getline(inp, tmp);
	inp >> tmp >> tmp >> tmp >> tmp;

	while (tmp != "BONDS" && !inp.eof())
	{
		getline(inp, tmp);
		for (int i = 0; i < 4; i++) inp >> tmp;
	}
	for (int j = 0; j<3; j++) getline(inp, tmp);

	for (int i = 0; i < numOfBonds; i++)
	{
		for (int j = 0; j < 9; j++)
			inp >> tmp;

		int inda, indb;
		inp >> inda >> tmp >> indb >> tmp;
		getline(inp, tmp);
		float x,y,z;
		inp >> tmp >> tmp >> x >>
			   tmp >> tmp >> y >> 
			   tmp >> tmp >> z;
		MolekularLink newLink = MolekularLink::createNewLinkInstance(_atoms[inda-1].getPosition(), _atoms[indb-1].getPosition());
		_links.push_back(newLink);

		for (int j = 0; j < 6; j++)
			getline(inp, tmp);
	}
}

void DataLoader::loadData(const std::string wfnPath, const std::string cptPath)
{
	std::ifstream inp(wfnPath);
	if (!inp.is_open()) {
		std::cout<< "File " <<wfnPath.c_str()<<" not found :(";
		return;
	}

	// readMolekuleName(inp);
	readAtoms(inp);
	inp.close();

	inp.open(cptPath);
	if (!inp.is_open()) {
		std::cout<< "File " <<cptPath.c_str()<<" not found :(";
		return;
	}
	readBonds(inp);
	inp.close();
}