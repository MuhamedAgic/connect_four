from connect_four_py import PyGame, PyOutcome


def wants_restart():
    while True:
        choice = input("Do you want to play again? (y/n): ").strip().lower()
        if choice in ['y', 'yes']:
            return True
        elif choice in ['n', 'no']:
            return False
        else:
            print("Please enter 'y' or 'n'.")


if __name__ == "__main__":
    print("🎮 Connect Four (Python + Rust FFI)")

    game = PyGame()
    print(game)

    playing = True
    while playing:
        print("Current player:", game.current_player())
        
        col = int(input("Choose column: "))

        try:
            result = game.play_move(col)
        except ValueError as e:
            print("Invalid move:", e)
            continue

        print(game)

        if result.outcome == PyOutcome.Win:
            print(f"Player {result.winner} wins!")
        elif result.outcome == PyOutcome.Draw:
            print("Draw!")
        elif result.outcome == PyOutcome.Exit:
            print("Game exited")

        if game.is_game_over():
            if wants_restart():
                print("Restarting game...")
                game.reset()
                print(game)
            else:
                print("Thanks for playing!")
                playing = False
