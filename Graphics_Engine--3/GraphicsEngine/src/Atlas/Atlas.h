#ifndef ATLAS_H
#define ATLAS_H

class Atlas
{
public:
	Atlas(int cols, int rows, int offsetX, int offsetY, float duration, int frameCount)
	{
		this->cols = cols;
		this->rows = rows;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->width = 0;
		this->height = 0;
		this->duration = duration;
		this->frameCount = frameCount;
		this->useSize = true;
	}

	~Atlas() { }

private:
	int cols = 1;
	int rows = 1;
	int offsetX = 0;
	int offsetY = 0;
	int width = 0;
	int height = 0;
	float duration = 1;
	int frameCount = 1;
	bool useSize = false;
	friend class Animation;
};
#endif // !ATLAS_H