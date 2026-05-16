package com.example;

import java.util.Scanner;

public class Main {

    static boolean askReplay(Scanner scanner) {
        while (true) {
            System.out.print("Do you want to play again? (y/n): ");
            String input = scanner.nextLine().trim().toLowerCase();

            if (input.equals("y")) return true;
            if (input.equals("n")) return false;

            System.out.println("Invalid input. Please enter 'y' or 'n'.");
        }
    }

    public static void main(String[] args) {
        System.out.println("🎮 Connect Four (Java + Rust FFI)");

        try (ConnectFourGame game = new ConnectFourGame();
             Scanner scanner = new Scanner(System.in).useDelimiter("\n");) {

            while (true) {

                while (!game.isOver()) {
                    System.out.println(game.board());
                    System.out.println("Player " + game.currentPlayer() + " turn");
                    System.out.print("Enter column: ");

                    String input = scanner.nextLine().trim();

                    int col;
                    try {
                        col = Integer.parseInt(input);
                    } catch (Exception e) {
                        System.out.println("Invalid input");
                        continue;
                    }

                    int result = game.play(col);

                    if (result >= 1) {
                        System.out.println("Player " + result + " wins!");
                    } else if (result == -2) {
                        System.out.println("Draw!");
                    } else if (result == -3) {
                        System.out.println("Invalid move!");
                    }
                }

                System.out.println(game.board());
                System.out.println("🏁 Game Over!");

                if (askReplay(scanner)) {
                    game.reset();
                    continue;
                }

                break;
            }

        }
    }
}