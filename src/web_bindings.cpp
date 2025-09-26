#include <emscripten/emscripten.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "Game.h"
#include "Message.h"

static Game *g_game = nullptr;

extern "C"
{

    EMSCRIPTEN_KEEPALIVE
    void js_init(int columns, int rows)
    {
        if (g_game)
        {
            delete g_game;
            g_game = nullptr;
        }
        int mines = std::max(1, (columns * rows) / 8);
        g_game = new Game(columns, rows, mines);
        std::cout << "Welcome to Minesweeper <3\n";
        std::cout << "Board: " << columns << "x" << rows << " (mines: " << mines << ")\n\n";
        g_game->print();
        std::cout << "\n";
        std::cout << "Instructions: Column (A-Z) + Row (1-26) + Action (F=Flag, R=Reveal)\n";
        std::cout << "Examples: A1, B5 F, C3 R | Reveal is default if no action specified\n";
    }

    EMSCRIPTEN_KEEPALIVE
    void js_submit(const char *text)
    {
        if (!g_game)
        {
            Message::warn("Initialize the game first (js_init)");
            return;
        }
        if (!text)
            return;

        std::string input(text);
        // Normalize to uppercase like in prompt()
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (!g_game->isValidInput(input))
        {
            Message::warn("Invalid format! Valid examples: A1, B3 F, C4 R");
            return;
        }

        auto [column, row, action] = g_game->parseInput(input);
        g_game->play(column, row, action);
        g_game->checkWinCondition();

        g_game->clear();
        g_game->print();

        if (g_game->isLost())
        {
            Message::warn("You lost the game!");
        }
        else if (g_game->isWon())
        {
            Message::warn("You won the game!");
        }
    }

    EMSCRIPTEN_KEEPALIVE
    int js_status_columns() { return g_game ? g_game->getColumns() : 0; }

    EMSCRIPTEN_KEEPALIVE
    int js_status_rows() { return g_game ? g_game->getRows() : 0; }

    EMSCRIPTEN_KEEPALIVE
    int js_status_mines_total() { return g_game ? g_game->getMinesTotal() : 0; }

    EMSCRIPTEN_KEEPALIVE
    int js_status_flags() { return g_game ? g_game->getFlagsCount() : 0; }

    EMSCRIPTEN_KEEPALIVE
    int js_status_revealed() { return g_game ? g_game->getRevealedCount() : 0; }

    // GameState as int (0: Playing, 1: Won, 2: Lost) per enums/GameState.h
    EMSCRIPTEN_KEEPALIVE
    int js_status_state() { return g_game ? g_game->getStateValue() : -1; }

} // extern "C"
