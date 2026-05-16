use crate::board::Board;
use crate::player::{Player, PlayerType};

const WIN_LEN: usize = 4;

#[derive(Debug, Clone)]
pub enum WinCondition {
    Horizontal,
    Vertical,
    Diagonal,
}

impl WinCondition {
    pub fn default_set() -> Vec<Self> {
        vec![Self::Horizontal, Self::Vertical, Self::Diagonal]
    }

    pub fn has_won(&self, player: &Player, board: &Board) -> bool {
        match self {
            Self::Horizontal => horizontal(player, board),
            Self::Vertical => vertical(player, board),
            Self::Diagonal => diagonal(player, board),
        }
    }
}

fn horizontal(player: &Player, board: &Board) -> bool {
    for row in &board.data {
        let mut count = 0;
        for &cell in row {
            if cell == player.id {
                count += 1;
                if count >= WIN_LEN {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }
    false
}

fn vertical(player: &Player, board: &Board) -> bool {
    for col in 0..board.col_count() {
        let mut count = 0;
        for row in 0..board.row_count() {
            if board.data[row][col] == player.id {
                count += 1;
                if count >= WIN_LEN {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }
    false
}

fn diagonal(player: &Player, board: &Board) -> bool {
    diag_se(player, board) || diag_ne(player, board)
}

fn diag_se(player: &Player, board: &Board) -> bool {
    let rows = board.row_count();
    let cols = board.col_count();

    for r in 0..=rows - WIN_LEN {
        for c in 0..=cols - WIN_LEN {
            if (0..WIN_LEN).all(|i| board.data[r + i][c + i] == player.id) {
                return true;
            }
        }
    }
    false
}

fn diag_ne(player: &Player, board: &Board) -> bool {
    let rows = board.row_count();
    let cols = board.col_count();

    for r in (WIN_LEN - 1)..rows {
        for c in 0..=cols - WIN_LEN {
            if (0..WIN_LEN).all(|i| board.data[r - i][c + i] == player.id) {
                return true;
            }
        }
    }
    false
}

#[cfg(test)]
mod tests {
    use super::*;

    fn player() -> Player {
        Player::new(1, "P1", 'x', PlayerType::Human)
    }

    #[test]
    fn horizontal_win() {
        let mut b = Board::new();
        let p = player();

        for i in 0..4 {
            b.data[5][i] = p.id;
        }

        assert!(WinCondition::Horizontal.has_won(&p, &b));
    }

    #[test]
    fn vertical_win() {
        let mut b = Board::new();
        let p = player();

        for i in 0..4 {
            b.data[i][0] = p.id;
        }

        assert!(WinCondition::Vertical.has_won(&p, &b));
    }

    #[test]
    fn diagonal_win() {
        let p = player();
        
        let mut b = Board::new();
        for i in 0..4 {
            b.data[i][i] = p.id;
        }

        let mut b2 = Board::new();
        for i in 0..4 {
            b2.data[b.row_count() - 1 - i][i] = p.id;
        }

        assert!(WinCondition::Diagonal.has_won(&p, &b));
        assert!(WinCondition::Diagonal.has_won(&p, &b2));
    }
}