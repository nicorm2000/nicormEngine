#include "Volume.h"

Volume::Volume()
{
	lines = nullptr;
}

Volume::~Volume()
{
	if (lines != nullptr)
	{
		delete lines;
		lines = nullptr;
	}
}

void Volume::DeInit()
{
	//if (lines != nullptr)
	//{
	//	lines->DeInit();
	//}
}