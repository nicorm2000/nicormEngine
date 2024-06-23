#ifndef BEHAVIOUR
#define BEHAVIOUR
#include "Component/Component.h"
namespace MikkaiEngine
{
	class GraficosEngine_API Behaviour : Component
	{
	protected:
		Behaviour();
		~Behaviour() {};
		void setEnabled(bool v) { enabled = v;		};
		bool getEnabled()		{ return enabled;	};
	private:
		bool enabled;
	};
}
#endif // !Behaviour
