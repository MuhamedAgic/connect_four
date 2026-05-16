package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func wantsReplay(reader *bufio.Reader) bool {
	for {
		fmt.Print("Do you want to play again? (y/n): ")

		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(strings.ToLower(input))

		switch input {
		case "y":
			return true
		case "n":
			return false
		default:
			fmt.Println("Invalid input")
		}
	}
}

func main() {
	fmt.Println("🎮 Connect Four (Go + Rust FFI)")

	g := New()
	defer g.Free()

	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println(g.Board())

		fmt.Printf("Player %d turn\n", g.CurrentPlayer())

		fmt.Print("Enter column: ")

		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)

		col, err := strconv.Atoi(input)
		if err != nil {
			fmt.Println("Invalid input")
			continue
		}

		result := g.Play(col)

		if result >= 1 {
			fmt.Printf("Player %d wins!\n", result)
		} else if result == -2 {
			fmt.Println("Draw!")
		} else if result == -3 {
			fmt.Println("Invalid move")
		}

		if g.IsOver() {
			if wantsReplay(reader) {
				fmt.Println("Restarting game...")
				g.Reset()
			} else {
				break
			}
		}
	}

	fmt.Println("Game over")
}
