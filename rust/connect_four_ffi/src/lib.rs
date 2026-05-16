use std::os::raw::c_void;

use connect_four_core::board::Board;
use connect_four_core::game::{Game, TurnOutcome, GameError};
use connect_four_core::player::{Player, PlayerType};
use connect_four_core::win_condition::WinCondition;

//
// Helpers
//

fn create_default_game() -> Game {
    Game::new(
        Board::new(),
        vec![
            Player::new(1, "Player1", 'X', PlayerType::Human),
            Player::new(2, "Player2", 'O', PlayerType::Computer),
        ],
        vec![
            WinCondition::Horizontal,
            WinCondition::Vertical,
            WinCondition::Diagonal,
        ],
    )
}

//
// Lifecycle
//

#[unsafe(no_mangle)]
pub extern "C" fn game_new() -> *mut c_void {
    let game = create_default_game();
    Box::into_raw(Box::new(game)) as *mut c_void
}

#[unsafe(no_mangle)]
pub extern "C" fn game_free(ptr: *mut c_void) {
    if ptr.is_null() { return;}
    unsafe {
        drop(Box::from_raw(ptr as *mut Game));
    }
}

//
// Game actions
//

#[unsafe(no_mangle)]
pub extern "C" fn game_make_move(ptr: *mut c_void, col: u32) -> i32 {
    if ptr.is_null() { return -1; }

    let game = unsafe { &mut *(ptr as *mut Game) };

    match game.play_move(col as usize) {
        Ok(outcome) => turn_outcome_to_int(outcome),
        Err(e) => game_error_to_int(e), 
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn game_get_current_player(ptr: *mut c_void) -> u32 {
    if ptr.is_null() { return 0; }
    let game = unsafe { &mut *(ptr as *mut Game) };
    game.current_player().id as u32
}

#[unsafe(no_mangle)]
pub extern "C" fn game_reset(ptr: *mut c_void) {
    if ptr.is_null() { return; }
    let game = unsafe { &mut *(ptr as *mut Game) };
    game.reset();
}

#[unsafe(no_mangle)]
pub extern "C" fn game_is_over(ptr: *mut c_void) -> i32 {
    if ptr.is_null() { return 1; }

    let game = unsafe { &*(ptr as *mut Game) };
    if game.is_game_over() {
        1
    } else {
        0
    }
}

//
// Board access (VERY IMPORTANT for UI/Java/etc)
//

#[unsafe(no_mangle)]
pub extern "C" fn game_get_cell(ptr: *mut c_void, row: u32, col: u32) -> u32 {
    if ptr.is_null() { return 0; }
    let game = unsafe { &*(ptr as *mut Game) };
    game.board().data[row as usize][col as usize] as u32
}

#[unsafe(no_mangle)]
pub extern "C" fn game_rows(ptr: *mut c_void) -> u32 {
    if ptr.is_null() { return 0; }
    let game = unsafe { &*(ptr as *mut Game) };
    game.board().row_count() as u32
}

#[unsafe(no_mangle)]
pub extern "C" fn game_cols(ptr: *mut c_void) -> u32 {
    if ptr.is_null() { return 0; }
    let game = unsafe { &*(ptr as *mut Game) };
    game.board().col_count() as u32
}

#[unsafe(no_mangle)]
pub extern "C" fn game_to_string(game: *const Game) -> *mut std::os::raw::c_char {
    let game = unsafe {
        assert!(!game.is_null());
        &*game
    };

    let s = format!("{}", game);

    std::ffi::CString::new(s)
        .unwrap()
        .into_raw()
}

#[unsafe(no_mangle)]
pub extern "C" fn free_string(ptr: *mut std::os::raw::c_char) {
    if ptr.is_null() { return; }
    unsafe {
        let _ = std::ffi::CString::from_raw(ptr);
    }
}

//
// Outcome mapping (FFI-safe)
//

fn turn_outcome_to_int(outcome: TurnOutcome) -> i32 {
    match outcome {
        TurnOutcome::Win(player_id) => player_id as i32,
        TurnOutcome::ContinueGame => 0,
        TurnOutcome::ExitGame => -1,
        TurnOutcome::Draw => -2,
    }
}

fn game_error_to_int(error: GameError) -> i32 {
    match error {
        GameError::InvalidMove => -3
    }
}