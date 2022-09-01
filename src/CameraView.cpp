#include "CameraView.h"
#include <GLFW/glfw3.h>

CameraView* CameraView::_singleton = nullptr;

CameraView& CameraView::get()
{
	if (!_singleton) {
		_singleton = new CameraView();
		return *_singleton;
	} else {
		return *_singleton;
	}
}

void CameraView::init(SGE* engine)
{
	_engine = engine;
}

void CameraView::rotateX(float angle)
{
	_engine->setViewTransition({0,0,0},angle,{1,0,0});
	glm::vec3 deltaRotation{angle,0,0};
	rotation += deltaRotation;
}

void CameraView::rotateY(float angle)
{
	_engine->setViewTransition({0,0,0},angle,{0,1,0});
	glm::vec3 deltaRotation{0,angle,0};
	rotation += deltaRotation;
}

void CameraView::rotateZ(float angle)
{
	_engine->setViewTransition({0,0,0},angle,{0,0,1});
	glm::vec3 deltaRotation{0,0,angle};
	rotation += deltaRotation;
}


void CameraView::moveStart()
{
	inMoving = true;
	glm::vec2 mousePos = _engine->getCursorPos();
	startMovingMousePos.x = mousePos.x;
	startMovingMousePos.y = mousePos.y;
	startMovingMousePos.z = 0;
}

void CameraView::moveUpdate()
{
	if (inMoving) {
		glm::vec3 currentMousePos;
		currentMousePos.x = _engine->getCursorPos().x;
		currentMousePos.y = _engine->getCursorPos().y;
		currentMousePos.z = 0;
		glm::vec3 deltaMousePos = currentMousePos - startMovingMousePos;
		deltaMousePos.y *= -1.f; // right is CCW
		rotateX(deltaMousePos.y);
		rotateY(deltaMousePos.x);
		rotateZ(deltaMousePos.z);
		startMovingMousePos = currentMousePos;
		rotation += deltaMousePos;
	}
}

void CameraView::moveEnd()
{
	inMoving = false;
}

void CameraView::moveCallback(int button, int action, int mods)
{
	CameraView& camera = CameraView::get();
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			camera.moveStart();
		} else if (action == GLFW_RELEASE) {
			camera.moveEnd();
		}
	}
}

void CameraView::reset()
{
	// rotateX(-rotation.x);
	// rotateY(-rotation.y);
	// rotateZ(-rotation.z);
}

void CameraView::keyCallback(int key, int scancode, int action, int mods)
{
	CameraView& camera = CameraView::get();
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		camera.reset();
	}
}

void CameraView::move(glm::vec3 deltaPos)
{
	position += deltaPos;
	_engine->setViewTransition(deltaPos);
}