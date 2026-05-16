package main

import "unsafe"

type Game struct {
	ptr unsafe.Pointer
}

func New() *Game {
	return &Game{
		ptr: NewGame(),
	}
}

func (g *Game) Free() {
	if g.ptr != nil {
		FreeGame(g.ptr)
		g.ptr = nil
	}
}

func (g *Game) Play(col int) int {
	return PlayMove(g.ptr, col)
}

func (g *Game) CurrentPlayer() int {
	return CurrentPlayer(g.ptr)
}

func (g *Game) IsOver() bool {
	return IsGameOver(g.ptr)
}

func (g *Game) Reset() {
	ResetGame(g.ptr)
}

func (g *Game) Board() string {
	return BoardString(g.ptr)
}
