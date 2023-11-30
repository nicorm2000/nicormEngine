#ifndef TIMER_H
#define TIMER_H

#include "GLFW/glfw3.h"
#include "Export.h"

class DllApi Timer
{
private:
	static float deltaTime;
	static double lastDeltaTime;
public:
	Timer();
	~Timer();
	static void Update(float currentTime);
	static float GetDeltaTime();
};

#endif
