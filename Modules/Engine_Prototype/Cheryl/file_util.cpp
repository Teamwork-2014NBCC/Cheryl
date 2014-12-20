#include <string>
#include "file_mgr.h"

//std::wstring& get_exec_path();

//std::wstring execution_path = get_exec_path();

std::wstring& get_exec_path()
{
	static wchar_t buffer[MAX_PATH];
	static bool done = false;
	if ( !done )
	{
		GetModuleFileName(NULL, buffer, MAX_PATH);
		done = true;
	}
	static std::wstring execution_path(buffer);
	return execution_path;
}