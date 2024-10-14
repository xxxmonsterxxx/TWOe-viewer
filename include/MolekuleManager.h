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

	glm::vec2 _cameraZLim{-5,20};
	float _cameraXYLim = 4;

	SGE& _engine = SGE::get();
	CameraObject& camera = _engine.getCameraObject();

	Molekule* _loadedMolekule;

	// molekule state
	bool _inRotation = false;
	bool _inMoving = false;
	int _zooming = 0;
	bool _hided = false;

	void setInRotation(bool inRotation);
	void setInMoving(bool inMoving);
	void zoom(int z);
	void hide();

	void updateRotation();
	void updateMoving();

	void reset();

	// handle mouse actions
	glm::vec2 _prevMousePos;
	static void mouseCallback(int button, int action, int mods);
	static void keyCallback(int key, int scancode, int action, int mods);
};