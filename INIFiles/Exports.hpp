#pragma once

#ifdef INI_INIFILES_EXPORTS

#define INIFILES __declspec(dllexport) 

#else

#define INIFILES __declspec(dllimport) 

#endif