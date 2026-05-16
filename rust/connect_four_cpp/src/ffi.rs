use connect_four_core::game::{Game as CoreGame, GameError, TurnOutcome};

#[cxx::bridge]
mod ffi {

    extern "Rust" {
        type Game;

        fn new_game() -> Box<Game>;
        fn play_move(game: &mut Game, col: usize) -> i32;
        fn current_player(game: &Game) -> usize;
        fn is_game_over(game: &Game) -> bool;
        fn board_string(game: &Game) -> String;
        fn reset(game: &mut Game);
    }
}

// -----------------------------
// FFI wrapper types
// -----------------------------

pub struct Game {
    game: CoreGame,
}

// -----------------------------
// Constructor
// -----------------------------

fn new_game() -> Box<Game> {
    Box::new(Game {
        game: CoreGame::default(),
    })
}

// -----------------------------
// Core FFI functions
// -----------------------------

// maybe add expressive enums later instead of i32 return type
fn play_move(game: &mut Game, col: usize) -> i32 {
    match game.game.play_move(col) {
        Ok(TurnOutcome::Win(id)) => id as i32,
        Ok(TurnOutcome::ContinueGame) => 0,
        Ok(TurnOutcome::ExitGame) => -1,
        Ok(TurnOutcome::Draw) => -2,
        Err(e) => {
            match e {
                GameError::InvalidMove => -3,
            }
        }
    }
}

fn current_player(game: &Game) -> usize {
    game.game.current_player().id
}

fn is_game_over(game: &Game) -> bool {
    game.game.is_game_over()
}

fn reset(game: &mut Game) {
    game.game.reset();
}

fn board_string(game: &Game) -> String {
    format!("{}", game.game)
}
