#pragma once

#ifdef EXPORT
#define DllApi   declspec( dllexport )
#else
#define DllApi   declspec( dllimport )
#endif