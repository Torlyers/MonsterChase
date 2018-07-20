#include "DebugTool/Debug.h"

#ifdef NDEBUG

void DEBUG_LOG(const char * data, ...)
{

}

#else
void DEBUG_LOG(const char * data, ...)
{
	ASSERT(data != nullptr);//check if data is nullptr

	const size_t lenTemp = 256;
	char strTemp[lenTemp] = "Debug Log: ";

	strcat_s(strTemp, data);
	strcat_s(strTemp, "\n");

	const size_t lenOutput = lenTemp + 32;

	char strOutput[lenOutput];

	// define a variable argument list variable 
	va_list args;

	// initialize it. second parameter is variable immediately
	// proceed variable arguments
	va_start(args, data);

	// (safely) print our formatted string to a char buffer
	vsprintf_s(strOutput, lenOutput, strTemp, args);

	va_end(args);

	DEBUG_SYSTEM();
	DEBUG_LOCATION();
	OutputDebugStringA(strOutput);
}

#endif // _DEBUG

void PROFILE_LOG(const char * data, ...)
{
#ifdef PROFILE
	ASSERT(data != nullptr);//check if data is nullptr

	const size_t lenTemp = 256;
	char strTemp[lenTemp] = "";

	strcat_s(strTemp, data);
	strcat_s(strTemp, "\n");

	const size_t lenOutput = lenTemp + 32;

	char strOutput[lenOutput];

	// define a variable argument list variable 
	va_list args;

	// initialize it. second parameter is variable immediately
	// proceed variable arguments
	va_start(args, data);

	// (safely) print our formatted string to a char buffer
	vsprintf_s(strOutput, lenOutput, strTemp, args);

	va_end(args);

	DEBUG_SYSTEM();
	DEBUG_LOCATION();
	OutputDebugStringA(strOutput);
#endif
}