package com.example;

import jnr.ffi.LibraryLoader;
import jnr.ffi.Pointer;

public interface ConnectFour {
    ConnectFour INSTANCE =
        LibraryLoader.create(ConnectFour.class)
            .load("connect_four_ffi");

    Pointer game_new();
    void game_free(Pointer game);

    int game_make_move(Pointer game, int col);
    int game_get_current_player(Pointer game);
    int game_is_over(Pointer game);
    void game_reset(Pointer game);
    
    Pointer game_to_string(Pointer game);
    void free_string(Pointer str);
}