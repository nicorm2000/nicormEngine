#include "Time.h"
#include <time.h>
#include <iostream>
Time::Time() {
	_deltaTime = 0;
	_unscaleDeltaTime = 0;
	_scale = 1;
	_lastTime = 0;
}
Time::~Time() {}
void Time::Update() {
	double actualTime = glfwGetTime();
	_unscaleDeltaTime = (actualTime - _lastTime);
	_deltaTime = _unscaleDeltaTime * _scale;
	_lastTime = actualTime;
}
void Time::SetScale(float scale) {
	_scale = scale;
}