#pragma once

#ifdef GUI_INTERFACE_EXPORTS

#define GUI_INTERFACE __declspec(dllexport) 

#else

#define GUI_INTERFACE __declspec(dllimport) 

#endif