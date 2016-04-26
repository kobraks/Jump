#pragma once


#ifdef MAPF_MAPFILE_EXPORTS

#define MAPF_MAPFILE __declspec(dllexport) 

#else

#define MAPF_MAPFILE __declspec(dllimport) 

#endif