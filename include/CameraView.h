#pragma once

#include "glm/glm.hpp"
#include <SGE/SGE.h>

class CameraView {
private:
	CameraView() {;}
	~CameraView() {;}

	static CameraView* _singleton;

	glm::vec3 startMovingMousePos;

	glm::vec3 position{0, 0, 0}; // position
	glm::vec3 rotation{0, 0, 0}; // rotation

	void moveStart();
	void moveEnd();

	bool inMoving = false;
	SGE* _engine;

	glm::vec3 _defaultPos;
	glm::vec3 _defaultRot;
public:

	static CameraView& get();

	void init(SGE* engine, glm::vec3 defaultPos={0,0,0}, glm::vec3 defaultRot={0,0,0});
	void setDefaultView(glm::vec3 defaultPos, glm::vec3 defaultRot);
	void setDefaultView();

	void rotate(glm::vec3 deltaRot);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void zoom(float zoomPos);
	void move(glm::vec3 deltaPos);
	void moveUpdate();
	void reset();

	static void moveCallback(int button, int action, int mods);
	static void keyCallback(int key, int scancode, int action, int mods);
};