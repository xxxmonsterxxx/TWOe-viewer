#include "MolekuleManager.h"

MolekuleManager* MolekuleManager::_singleton = nullptr;

MolekuleManager& MolekuleManager::get()
{
	if (!_singleton) {
		_singleton = new MolekuleManager();
		return *_singleton;
	} else {
		return *_singleton;
	}
}

void MolekuleManager::setInRotation(bool inRotation)
{
	if (!_inRotation && inRotation) {
		_prevMousePos = _engine.getCursorPos();
	}

	_inRotation = inRotation;
}

void MolekuleManager::setInMoving(bool inMoving)
{
	if (!_inMoving && inMoving) {
		_prevMousePos = _engine.getCursorPos();
	}

	_inMoving = inMoving;
}

void MolekuleManager::zoom(int z)
{
	if (_zooming != z) {
		_zooming = z;
	}
}

void MolekuleManager::updateRotation()
{
	if (_inRotation) {
		glm::vec2 currMousePos = _engine.getCursorPos();
		glm::vec2 deltaMousePos = currMousePos - _prevMousePos;
		deltaMousePos.y *= -1.f; // right is CCW
		_loadedMolekule->rotate(deltaMousePos.y, deltaMousePos.x, 0);
		_prevMousePos = currMousePos;
	}
}

void MolekuleManager::updateMoving()
{
	if (_inMoving) {
		glm::vec2 currMousePos = _engine.getCursorPos();
		glm::vec2 deltaMousePos = currMousePos - _prevMousePos;
		deltaMousePos.y *= -1.f; // right is CCW
		_loadedMolekule->move({deltaMousePos.x*0.01f, -deltaMousePos.y*0.01f, 0});
		_prevMousePos = currMousePos;
	}

	if (_zooming > 0)
		_loadedMolekule->move({0, 0, 0.1f});
	else if (_zooming < 0)
		_loadedMolekule->move({0, 0, -0.1f});
}

void MolekuleManager::update()
{
	updateRotation();
	updateMoving();
}

void MolekuleManager::mouseCallback(int button, int action, int mods)
{
	MolekuleManager& mm = MolekuleManager::get();

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mm.setInRotation(true);
		} else if (action == GLFW_RELEASE) {
			mm.setInRotation(false);
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			mm.setInMoving(true);
		} else if (action == GLFW_RELEASE) {
			mm.setInMoving(false);
		}
	}
}

void MolekuleManager::keyCallback(int key, int scancode, int action, int mods)
{
	MolekuleManager& mm = MolekuleManager::get();

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			mm.zoom(1);
		}
		if (action == GLFW_RELEASE) {
			mm.zoom(0);
		}
	}

	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			mm.zoom(-1);
		}
		if (action == GLFW_RELEASE) {
			mm.zoom(0);
		}
	}
	
}

void MolekuleManager::init()
{
	_engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, mouseCallback);
	_engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, mouseCallback);
	_engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, mouseCallback);
	_engine.mouseEventSubscribe(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, mouseCallback);

	_engine.keyEventSubscribe(GLFW_KEY_W, GLFW_PRESS, keyCallback);
	_engine.keyEventSubscribe(GLFW_KEY_W, GLFW_RELEASE, keyCallback);
	_engine.keyEventSubscribe(GLFW_KEY_S, GLFW_PRESS, keyCallback);
	_engine.keyEventSubscribe(GLFW_KEY_S, GLFW_RELEASE, keyCallback);
}

void MolekuleManager::setLoadedMolekule(Molekule* m)
{
	_loadedMolekule = m;
}

Molekule* MolekuleManager::getLoadedMolekule()
{
	return _loadedMolekule;
}