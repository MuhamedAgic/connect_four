package com.example;

import jnr.ffi.Pointer;

public class ConnectFourGame implements AutoCloseable {
    private final ConnectFour lib = ConnectFour.INSTANCE;
    private final Pointer ptr;

    public ConnectFourGame() {
        this.ptr = lib.game_new();
    }

    public int play(int col) {
        return lib.game_make_move(ptr, col);
    }

    public boolean isOver() {
        return lib.game_is_over(ptr) != 0;
    }

    public String board() {
        Pointer p = lib.game_to_string(ptr);
        String s = p.getString(0);
        lib.free_string(p);
        return s;
    }

    public int currentPlayer() {
        return lib.game_get_current_player(ptr);
    }

    @Override
    public void close() {
        lib.game_free(ptr);
    }

    public void reset() {
        lib.game_reset(ptr);
    }
}