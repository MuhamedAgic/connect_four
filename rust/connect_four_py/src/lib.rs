use pyo3::prelude::*;
use pyo3::exceptions::PyValueError;

use connect_four_core::game::{Game, TurnOutcome, GameError};

#[pyclass]
pub struct PyGame {
    game: Game
}

#[pyclass(skip_from_py_object)]
#[derive(Clone)]
pub enum PyOutcome {
    Continue,
    Win,
    Draw,
    Exit,
}

#[pyclass(skip_from_py_object)]
pub struct PyMoveResult {
    #[pyo3(get)]
    pub outcome: PyOutcome,

    #[pyo3(get)]
    pub winner: Option<usize>,
}

#[pymethods]
impl PyGame {

    #[new]
    fn new() -> Self {
        Self {
            game: Game::default(),
        }
    }

    fn __str__(&self) -> String {
        format!("{}", self.game)
    }

    pub fn play_move(&mut self, col: usize) -> PyResult<PyMoveResult> {
        match self.game.play_move(col) {
            Ok(outcome) => Ok(map_outcome(outcome)),
            Err(GameError::InvalidMove) => {
                Err(PyValueError::new_err("Invalid move"))
            }
        }
    }

    pub fn reset(&mut self) {
        self.game.reset();
    }

    pub fn current_player(&self) -> usize {
        self.game.current_player().id
    }

    pub fn is_game_over(&self) -> bool {
        self.game.is_game_over()
    }

    pub fn get_board(&self) -> Vec<Vec<usize>> {
        self.game.board.data
            .iter()
            .map(|row| row.to_vec())
            .collect()
    }

    pub fn rows(&self) -> usize {
        self.game.board.row_count()
    }

    pub fn cols(&self) -> usize {
        self.game.board.col_count()
    }
}

//
// Helper mapping
//

fn map_outcome(outcome: TurnOutcome) -> PyMoveResult {
    match outcome {
        TurnOutcome::ContinueGame => PyMoveResult {
            outcome: PyOutcome::Continue,
            winner: None,
        },
        TurnOutcome::ExitGame => PyMoveResult {
            outcome: PyOutcome::Exit,
            winner: None,
        },
        TurnOutcome::Draw => PyMoveResult {
            outcome: PyOutcome::Draw,
            winner: None,
        },
        TurnOutcome::Win(id) => PyMoveResult {
            outcome: PyOutcome::Win,
            winner: Some(id),
        },
    }
}

//
// Module
//

#[pymodule]
fn connect_four_py(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_class::<PyGame>()?;
    m.add_class::<PyMoveResult>()?;
    m.add_class::<PyOutcome>()?;
    Ok(())
}