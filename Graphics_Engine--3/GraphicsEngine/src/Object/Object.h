#ifndef OBJECT_H
#define OBJECT_H

#include "Exports/Exports.h"
#include "HideFlags.h"
#include <string>
#include <list>
using namespace std;
namespace MikkaiEngine
{
	class GraficosEngine_API Object
	{
	public:

		Object();
		~Object();
		void AddDescription(string name);

		string GetDescription() { return _baseDescription; };
	protected:

		string GetnameOBJ();
		void SetnameOBJ(string name);

		bool operator==(const Object& x) const;
		bool operator!=(const Object& x) const;
	private:
			//
			// Resumen:
			//     The name of the object.
		string _name;
		string _baseDescription;
		int m_instanceID;
		int static m_index;
		static list<Object*> lisObjects;
	};
}
#endif // !OBJECT_H