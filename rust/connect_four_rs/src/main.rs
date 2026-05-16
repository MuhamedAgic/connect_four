use std::io::{self, Write};

use connect_four_core::game::{Game, TurnOutcome, GameError};

fn read_input() -> Option<usize> {
    print!("Enter column: ");
    io::stdout().flush().ok()?;

    let mut input = String::new();
    io::stdin().read_line(&mut input).ok()?;

    input.trim().parse::<usize>().ok()
}

fn ask_restart() -> bool {
    println!("Play again? (y/n)");

    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();

    match input.trim() {
        "y" | "Y" => true,
        "n" | "N" => false,
        _ => {
            println!("Invalid input. Please enter 'y' or 'n'.");
            ask_restart() // ask again on invalid input
        }
    }
}

pub fn run(game: &mut Game) {
    println!("Welcome to Connect Four!");

    while !game.is_game_over() {
        println!("{}", game);

        let player = game.current_player();
        println!("Player {} ({}) turn", player.id, player.marker);

        let col = match read_input() {
            Some(c) => c,
            None => {
                println!("Invalid input");
                continue;
            }
        };

        match game.play_move(col) {
            Ok(TurnOutcome::ContinueGame) => continue,
            Ok(TurnOutcome::Win(player_id)) => {
                println!("{}", game);
                println!("Player {} wins!", player_id);
            }
            Ok(TurnOutcome::Draw) => {
                println!("{}", game);
                println!("It's a draw!");
            },
            Ok(TurnOutcome::ExitGame) => {
                println!("Game ended!");
                break;
            }
            Err(e) => {
                match e {
                    GameError::InvalidMove => {
                        println!("Invalid move, try again.");
                    }
                }
            }
        }
    }

    println!("Game over!");
}

fn main() {
    loop {
        let mut game = Game::default();
        run(&mut game);

        if !ask_restart() {
            break;
        }
    }
}