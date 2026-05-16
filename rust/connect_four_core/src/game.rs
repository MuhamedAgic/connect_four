use core::fmt;

use crate::board::Board;
use crate::player::{Player, PlayerType};
use crate::win_condition::WinCondition;

#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum TurnOutcome {
    ContinueGame,
    ExitGame,
    Win(usize),
    Draw
}


#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum GameError {
    InvalidMove
}

pub struct Game {
    pub board: Board,
    pub players: Vec<Player>,
    win_conditions: Vec<WinCondition>,
    current_player_index: usize,
    game_over: bool,
}

impl Game {
    pub fn new(
        board: Board,
        players: Vec<Player>,
        win_conditions: Vec<WinCondition>,
    ) -> Self {
        Self {
            board,
            players,
            win_conditions,
            current_player_index: 0,
            game_over: false,
        }
    }

    pub fn default() -> Self {
        Self::new(
            Board::new(),
            vec![
                Player::new(1, "P1", 'x', PlayerType::Human),
                Player::new(2, "P2", 'o', PlayerType::Computer),
            ],
            WinCondition::default_set(),
        )
    }

    pub fn board(&self) -> &Board {
        &self.board
    }

    pub fn play_move(&mut self, col: usize) -> Result<TurnOutcome, GameError> {
        if self.game_over {
            return Ok(TurnOutcome::ExitGame);
        }

        let player = &self.players[self.current_player_index];

        let row = match self.board.apply_gravity(col) {
            Some(r) => r,
            None => return Err(GameError::InvalidMove),
        };

        self.board.data[row][col] = player.id;

        if self.has_won(player) {
            self.game_over = true;
            return Ok(TurnOutcome::Win(player.id));
        }

        if self.board.is_full() {
            self.game_over = true;
            return Ok(TurnOutcome::Draw);
        }

        self.current_player_index = (self.current_player_index + 1) % self.players.len();

        Ok(TurnOutcome::ContinueGame)
    }

    fn has_won(&self, player: &Player) -> bool {
        self.win_conditions
            .iter()
            .any(|wc| wc.has_won(player, &self.board))
    }

    pub fn reset(&mut self) {
        self.board.clear();
        self.current_player_index = 0;
        self.game_over = false;
    }

    pub fn current_player(&self) -> &Player {
        &self.players[self.current_player_index]
    }

    pub fn is_game_over(&self) -> bool {
        self.game_over
    }
}

impl fmt::Display for Game {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let board = &self.board;

        print!(" ");
        for c in 0..board.col_count() {
            print!(" {} ", c);
        }
        println!();
        print!(" ");
        for _ in 0..board.col_count() {
            print!("---");
        }
        println!();

        for row in board.data.iter() {
            print!("|");
            for cell in row.iter() {
                let symbol = match cell {
                    0 => ' ',
                    1 => 'x',
                    2 => 'o',
                    3 => '#',
                    4 => 'v',
                    _ => '?'
                };
                print!(" {} ", symbol);
            }
            println!("|");
        }
        print!(" ");
        for _ in 0..board.col_count() {
            print!("---");
        }
        println!();

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn game() -> Game {
        Game::default()
    }

    #[test]
    fn first_move_updates_board() {
        let mut g = game();
        let res = g.play_move(0);

        assert_eq!(res, Ok(TurnOutcome::ContinueGame));
        assert_eq!(g.board.data[5][0], 1);
    }

    #[test]
    fn turn_switches() {
        let mut g = game();
        g.play_move(0);

        assert_eq!(g.current_player().id, 2);
    }

    #[test]
    fn invalid_move() {
        let mut g = game();
        let res = g.play_move(100);

        assert_eq!(res, Err(GameError::InvalidMove));
    }

    #[test]
    fn horizontal_win() {
        let mut g = game();

        g.play_move(0);
        g.play_move(0);
        g.play_move(1);
        g.play_move(1);
        g.play_move(2);
        g.play_move(2);
        let res = g.play_move(3);

        assert_eq!(res, Ok(TurnOutcome::Win(1)));
    }

    #[test]
    fn draw_game() {
        let mut g = game();

        for col in 0..7 {
            for _ in 0..6 {
                g.play_move(col);
            }
        }

        assert!(g.is_game_over());
    }
}