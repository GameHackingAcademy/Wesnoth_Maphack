# Wesnoth Map Hack
Referenced in https://gamehacking.academy/lesson/4/2.

A map hack for Wesnoth 1.14.9 that reveals the entire map by removing in-game fog-of-war.

This is done by modifying the game's code responsible for re-setting all tiles to a hidden state at the start of a player's turn. This code is modified to set all tiles to a visible state (-1, or 0xFFFFFFFF in Wesnoth). To fit in the space of the previous instructions, this is done through the use of an `or dword ptr ds:[esi],0xFFFFFFFF` instruction (opcode 0x830EFF), along with several nop's (0x90).

This must be injected into the Wesnoth process to work. One way to do this is to use a DLL injector. Another way is to enable AppInit_DLLs in the registry.
