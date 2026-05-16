const ROWS: usize = 6;
const COLS: usize = 7;
const EMPTY: usize = 0;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Board {
    pub data: [[usize; COLS]; ROWS],
}

impl Board {
    pub fn new() -> Self {
        Self {
            data: [[EMPTY; COLS]; ROWS],
        }
    }

    pub fn apply_gravity(&self, col: usize) -> Option<usize> {
        if !self.is_valid_move(col) {
            return None;
        }

        for row in (0..ROWS).rev() {
            if self.data[row][col] == EMPTY {
                return Some(row);
            }
        }
        None
    }

    pub fn is_valid_move(&self, col: usize) -> bool {
        col < COLS && self.data[0][col] == EMPTY
    }

    pub fn is_full(&self) -> bool {
        self.data[0].iter().all(|&c| c != EMPTY)
    }

    pub fn clear(&mut self) {
        self.data = [[EMPTY; COLS]; ROWS];
    }

    pub fn row_count(&self) -> usize {
        ROWS
    }

    pub fn col_count(&self) -> usize {
        COLS
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn gravity() {
        let b = Board::new();
        assert_eq!(b.apply_gravity(0), Some(5));
    }

    #[test]
    fn column_full() {
        let mut b = Board::new();

        for _ in 0..6 {
            let r = b.apply_gravity(0).unwrap();
            b.data[r][0] = 1;
        }

        assert_eq!(b.apply_gravity(0), None);
    }

    #[test]
    fn full_board() {
        let mut b = Board::new();

        for col in 0..7 {
            for _ in 0..6 {
                let r = b.apply_gravity(col).unwrap();
                b.data[r][col] = 1;
            }
        }

        assert!(b.is_full());
    }
}