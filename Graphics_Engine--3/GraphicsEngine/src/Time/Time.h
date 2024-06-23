#ifndef TIME_H
#define TIME_H
#include "../Exports/Exports.h"
class GraficosEngine_API Time {
private:
	float _unscaleDeltaTime;
	float _scale;
	double _lastTime;
public:
	float _deltaTime;
	Time();
	~Time();
	void Update();
	void SetScale(float scale);
};


#endif