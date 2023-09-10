#pragma once

#ifdef EXPORT
#define DllApi   __declspec(dllexport)
#else
#define DllApi   __declspec(dllexport)
#endif