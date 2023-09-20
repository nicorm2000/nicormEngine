#pragma once

#ifdef DllApi
#define DllApi   __declspec(dllexport)
#else
#define DllApi   __declspec(dllimport)
#endif