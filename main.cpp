#include <Windows.h>

unsigned char new_bytes[8] = { 0x90, 0x90, 0x90, 0x83, 0x0E, 0xFF, 0x90, 0x90 };

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x6CD519;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		VirtualProtect((void*)hook_location, 8, PAGE_EXECUTE_READWRITE, &old_protect);
		for (int i = 0; i < sizeof(new_bytes); i++) {
			*(hook_location + i) = new_bytes[i];
		}
	}

	return true;
}
