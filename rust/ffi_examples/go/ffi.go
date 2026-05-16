package main

/*
#cgo LDFLAGS: -L. -lconnect_four_ffi

#include <stdint.h>

extern void* game_new();
extern void game_free(void* game);

extern int32_t game_make_move(void* game, uint32_t col);
extern uint32_t game_get_current_player(void* game);

extern int32_t game_is_over(void* game);

extern char* game_to_string(void* game);
extern void free_string(char* s);

extern void game_reset(void* game);
*/
import "C"

import "unsafe"

func NewGame() unsafe.Pointer {
	return C.game_new()
}

func FreeGame(ptr unsafe.Pointer) {
	C.game_free(ptr)
}

func PlayMove(ptr unsafe.Pointer, col int) int {
	return int(C.game_make_move(ptr, C.uint(col)))
}

func CurrentPlayer(ptr unsafe.Pointer) int {
	return int(C.game_get_current_player(ptr))
}

func IsGameOver(ptr unsafe.Pointer) bool {
	return C.game_is_over(ptr) != 0
}

func ResetGame(ptr unsafe.Pointer) {
	C.game_reset(ptr)
}

func BoardString(ptr unsafe.Pointer) string {
	s := C.game_to_string(ptr)
	defer C.free_string(s)
	return C.GoString(s)
}
