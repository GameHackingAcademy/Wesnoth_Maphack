/*
	A maphack for Wesnoth 1.14.9 that reveals the entire map by removing in-game fog-of-war.

	This is done by modifying the game's code responsible for resetting all tiles to a hidden state at the start of a player's turn. 
	This code is modified to set all tiles to a visible state (-1 or 0xFFFFFFFF in Wesnoth). To fit in the space of the previous instructions, 
	this is done through the use of an or dword ptr ds:[esi],0xFFFFFFFF instruction (opcode 0x830EFF) along with several NOPs (0x90).

	This must be injected into the Wesnoth process to work. One way to do this is to use a DLL injector. 
	Another way is to enable AppInit_DLLs in the registry.

	The offsets and method to discover them are discussed in the article at: https://gamehacking.academy/lesson/20
*/
#include <Windows.h>

// The new opcodes to write into the game's code
unsigned char new_bytes[8] = { 0x90, 0x90, 0x90, 0x83, 0x0E, 0xFF, 0x90, 0x90 };

// When our DLL is attached, first unprotect the memory responsible for resetting the tiles in the game
// Then, write our new opcodes into that memory location
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
