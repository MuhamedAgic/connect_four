using System;

class Program
{
    static bool AskReplay()
    {
        while (true)
        {
            Console.Write("Do you want to play again? (y/n): ");
            string? input = Console.ReadLine();

            if (input == null)
                continue;

            input = input.Trim().ToLower();

            if (input == "y")
                return true;

            if (input == "n")
                return false;

            Console.WriteLine("Invalid input. Please enter 'y' or 'n'.");
        }
    }

    static void Main()
    {
        using var game = new ConnectFour();

        Console.WriteLine("🎮 Connect Four (C# + Rust FFI)");
        Console.WriteLine("--------------------------------");

        while (true)
        {
            while (!game.IsGameOver())
            {
                Console.Clear();

                Console.WriteLine(game.Board());
                Console.WriteLine();
                Console.WriteLine($"Player {game.CurrentPlayer()}'s turn");
                Console.Write("Enter column: ");

                var input = Console.ReadLine();

                if (!int.TryParse(input, out int col))
                {
                    Console.WriteLine("Invalid input. Press Enter...");
                    Console.ReadLine();
                    continue;
                }

                int result = game.PlayMove(col);

                if (result >= 1)
                {
                    Console.WriteLine($"Player {result} wins!");
                }
                else if (result == -2)
                {
                    Console.WriteLine("Draw!");
                }
                else if (result == -3)
                {
                    Console.WriteLine("Invalid move!");
                }
            }

            Console.Clear();
            Console.WriteLine(game.Board());
            Console.WriteLine("🏁 Game Over!");

            if (AskReplay())
            {
                game.Reset();
                continue;
            }

            break;
        }

        Console.WriteLine("Goodbye!");
    }
}