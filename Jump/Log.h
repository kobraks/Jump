#pragma once

#include <sstream>
#include <string>
#include <stdio.h>

inline std::string NowTime();

enum TLogLevel { logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4 };

static unsigned __int64 lineNumber = 0;

template <typename T>
class Log
{
public:
	Log();
	virtual ~Log();
	std::ostringstream& Get(TLogLevel level = logINFO);
public:
	static TLogLevel& ReportingLevel();
	static bool& isEnabled();
	static std::string ToString(TLogLevel level);
	static TLogLevel FromString(const std::string& level);
protected:
	std::ostringstream os;
private:
	Log(const Log&);
	Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::Get(TLogLevel level)
{
	lineNumber++;
	os << lineNumber << " - " << NowTime();
	os << " " << ToString(level) << ": ";
	os << std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
	return os;
}

template <typename T>
Log<T>::~Log()
{
	os << std::endl;
	T::Output(os.str());
}

template <typename T>
TLogLevel& Log<T>::ReportingLevel()
{
	static TLogLevel reportingLevel = logDEBUG4;
	return reportingLevel;
}

template <typename T>
bool& Log<T>::isEnabled()
{
	static bool enabled = true;
	return enabled;
}

template <typename T>
std::string Log<T>::ToString(TLogLevel level)
{
	static const char* const buffer[] = { "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4" };
	return buffer[level];
}

template <typename T>
TLogLevel Log<T>::FromString(const std::string& level)
{
	if (level == "DEBUG4")
		return logDEBUG4;
	if (level == "DEBUG3")
		return logDEBUG3;
	if (level == "DEBUG2")
		return logDEBUG2;
	if (level == "DEBUG1")
		return logDEBUG1;
	if (level == "DEBUG")
		return logDEBUG;
	if (level == "INFO")
		return logINFO;
	if (level == "WARNING")
		return logWARNING;
	if (level == "ERROR")
		return logERROR;
	Log<T>().Get(logWARNING) << "Unknown logging level '" << level << "'. Using INFO level as default.";
	return logINFO;
}

class Output2FILE
{
public:
	static FILE*& Stream();
	static void Output(const std::string& msg);
};

inline FILE*& Output2FILE::Stream()
{
	static FILE* pStream = stderr;
	return pStream;
}

inline void Output2FILE::Output(const std::string& msg)
{
	FILE* pStream = Stream();
	if (!pStream)
		return;
	fprintf(pStream, "%s", msg.c_str());
	fflush(pStream);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   if defined (BUILDING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllexport)
#   elif defined (USING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllimport)
#   else
#       define FILELOG_DECLSPEC
#   endif // BUILDING_DBSIMPLE_DLL
#else
#   define FILELOG_DECLSPEC
#endif // _WIN32

class FILELOG_DECLSPEC FILELog : public Log<Output2FILE> {};
//typedef Log<Output2FILE> FILELog;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG4
#endif

#define FILE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
			    else if (level > FILELog::ReportingLevel()  || !Output2FILE::Stream()) ; \
			    else if (FILELog::isEnabled()) FILELog().Get(level) 

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime()
{
	const int MAX_LEN = 200;
	char buffer[MAX_LEN];
	if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
		"HH':'mm':'ss", buffer, MAX_LEN) == 0)
		return "Error in NowTime()";

	char result[100] = { 0 };
	static DWORD first = GetTickCount();
std:sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
	return result;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
	char buffer[11];
	time_t t;
	time(&t);
	tm r = { 0 };
	strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
	struct timeval tv;
	gettimeofday(&tv, 0);
	char result[100] = { 0 };
	std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
	return result;
}

#endif //WIN32

inline void systemInformation()
{
	//pobieranie informacji o komputerze
	SYSTEM_INFO system;
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);
	GetNativeSystemInfo(&system);

	FILE_LOG(logINFO) << std::endl
		<< "		<Hardware information>" << std::endl
		<< "				OEM ID: " << system.dwOemId << std::endl << std::endl

		<< "			<Processor information>" << std::endl
		<< "				Proccesor name: " << []()->std::string {

		// Get extended ids.
		int CPUInfo[4] = { -1 };
		__cpuid(CPUInfo, 0x80000000);
		unsigned int nExIds = CPUInfo[0];

		// Get the information associated with each extended ID.
		char CPUBrandString[0x40] = { 0 };
		for (unsigned int i = 0x80000000; i <= nExIds; ++i)
		{
			__cpuid(CPUInfo, i);

			// Interpret CPU brand string and cache information.
			if (i == 0x80000002)
			{
				memcpy(CPUBrandString,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000003)
			{
				memcpy(CPUBrandString + 16,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000004)
			{
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
			}
		}

		return CPUBrandString;
	}() << std::endl
		<< "				Processor architecture: " << [](SYSTEM_INFO system)->std::string {
		switch (system.wProcessorArchitecture)
		{
		case 9:
			return "64bit";
		case 5:
			return "ARM";
		case 6:
			return "Intel Itanium";
		case 0:
			return "x86";
		default:
			return "unknown";
		}

	}(system) << std::endl
		<< "				Number of processor: " << system.dwNumberOfProcessors << std::endl
		<< "				Processor type: " << system.dwProcessorType << std::endl
		<< "				Processor revision: " << system.wProcessorRevision << std::endl
		<< "				Active processor mask: " << system.dwActiveProcessorMask << std::endl << std::endl

		<< "			<Memory information>" << std::endl
		<< "				total MB of physical memory: " << statex.ullTotalPhys / 1024 << std::endl
		<< "				free  MB of physical memory: " << statex.ullAvailPhys / 1024 << std::endl
		<< "				total MB of paging file: " << statex.ullTotalPageFile / 1024 << std::endl
		<< "				free  MB of paging file: " << statex.ullAvailPageFile / 1024 << std::endl
		<< "				total MB of virtual memory: " << statex.ullTotalVirtual / 1024 << std::endl
		<< "				free  MB of virtual memory: " << statex.ullAvailVirtual / 1024 << std::endl
		<< "				Page size: " << system.dwPageSize << std::endl
		<< "				Minimum application address: " << system.lpMinimumApplicationAddress << std::endl
		<< "				Maximum application address: " << system.lpMaximumApplicationAddress << std::endl
		<< "		<Hardware information>" << std::endl;
}