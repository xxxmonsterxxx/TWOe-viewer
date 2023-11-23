#pragma once

#include "TwoeUnits.h"

// molekule manager allows load, show/hide, rotate, move selected molekule
class MolekuleManager {
public:
	void init();
	static MolekuleManager& get();

	void setLoadedMolekule(Molekule* m);
	Molekule* getLoadedMolekule();

	void update();

private:
	static MolekuleManager* _singleton;

	SGE& _engine = SGE::get();

	Molekule* _loadedMolekule;

	// molekule state
	bool _inRotation = false;
	bool _inMoving = false;

	void setInRotation(bool inRotation);
	void setInMoving(bool inMoving);

	// handle mouse actions
	glm::vec2 _prevMousePos;
	static void mouseCallback(int button, int action, int mods);
};