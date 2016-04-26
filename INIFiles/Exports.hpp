#pragma once

#ifdef INI_INIFILES_EXPORTS

#define INI_INIFILES __declspec(dllexport) 

#else

#define INI_INIFILES __declspec(dllimport) 

#endif