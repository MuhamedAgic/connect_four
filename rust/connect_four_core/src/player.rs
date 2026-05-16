
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PlayerType {
    Human = 0,
    Computer = 1
}

#[derive(Debug, Clone)]
pub struct Player {
    pub id: usize,
    pub name: String,
    pub marker: char,
    pub player_type: PlayerType,
}

impl Player {
    pub fn new(id: usize, name: impl Into<String>, marker: char, player_type: PlayerType) -> Self {
        Self {
            id,
            name: name.into(),
            marker,
            player_type
        }
    }
}