/**
 * @file web_bindings.cpp
 * @brief Emscripten interop layer exposing core Minesweeper game functions to JavaScript.
 * @author ayrto
 * @date 26/09/2025
 * This file defines a small C-style API (exported with EMSCRIPTEN_KEEPALIVE) that the
 * web front-end calls via Module.cwrap()/Module.ccall(). It owns a single dynamic Game
 * instance (g_game) and forwards user actions, enforcing backend-side safety constraints
 * (board size clamping, input validation, safe cleanup between sessions).
 *
 * NOTE: All exported symbols are wrapped in extern "C" to avoid C++ name mangling so
 * JavaScript can reference them by their exact names!
 */
#include <emscripten/emscripten.h>
#include <string>
#include <iostream>
#include <algorithm>

#include "Game.h"
#include "Message.h"

/**
 * @brief Owning pointer to the active Game instance for the web session.
 *        A single instance model keeps the interop surface minimal.
 */
static Game *g_game = nullptr;

extern "C" {
/**
 * @brief Initialize (or re-initialize) the game from JavaScript.
 * @param columns Requested number of columns (will be clamped to [5,15]).
 * @param rows Requested number of rows (will be clamped to [5,15]).
 *
 * Destroys any previous Game, clamps dimensions for safety / consistency with the native
 * version, computes a mine count (~12.5% density), prints a welcome header and the initial
 * board. A note is printed if the requested size was adjusted.
 */
EMSCRIPTEN_KEEPALIVE
void js_init(int columns, int rows) {
    if (g_game) {
        // Dispose previous session if any
        delete g_game;
        g_game = nullptr;
    }

    // Backend-enforced constraints (mirrors native validation)
    int origCols = columns;
    int origRows = rows;
    if (columns < 5) columns = 5;
    else if (columns > 15) columns = 15;
    if (rows < 5) rows = 5;
    else if (rows > 15) rows = 15;
    bool adjusted = (origCols != columns) || (origRows != rows);

    int mines = std::max(1, (columns * rows) / 8); // Mine density heuristic
    g_game = new Game(columns, rows, mines);
    std::cout << "Welcome to Minesweeper <3\n";
    std::cout << "Board: " << columns << "x" << rows << " (mines: " << mines << ")\n\n";
    if (adjusted)
        std::cout << "[Requested size " << origCols << "x" << origRows << " adjusted to allowed range 5..15]" <<
                std::endl;
    g_game->print();
    std::cout << "\n";
}

/**
 * @brief Submit a text command from JavaScript (e.g. "A1", "B5 F", "C3 R").
 * @param text Null-terminated UTF-8 input string from the web UI.
 *
 * Steps:
 *  1. Validate game instance exists.
 *  2. Normalize to uppercase for uniform parsing.
 *  3. Validate syntax using Game::isValidInput().
 *  4. Parse (column,row,action) and apply the move.
 *  5. Check win condition, clear screen, re-print board.
 *  6. Emit win / lose message if terminal state reached.
 */
EMSCRIPTEN_KEEPALIVE
void js_submit(const char *text) {
    if (!g_game) {
        Message::warn("Initialize the game first (js_init)");
        return;
    }
    if (!text) return; // Defensive guard

    std::string input(text);
    // Normalize to uppercase (C++20 ranges variant)
    std::ranges::transform(input, input.begin(), ::toupper);

    if (!g_game->isValidInput(input)) {
        Message::warn("Invalid format! Valid examples: A1, B3 F, C4 R");
        return;
    }

    auto [column, row, action] = g_game->parseInput(input);
    g_game->play(column, row, action);
    g_game->checkWinCondition();

    g_game->clear();
    g_game->print();

    if (g_game->isLost()) {
        Message::warn("You lost the game!");
    } else if (g_game->isWon()) {
        Message::warn("You won the game!");
    }
}

/** @brief Return active board column count (0 if no game). */
EMSCRIPTEN_KEEPALIVE
int js_status_columns() { return g_game ? g_game->getColumns() : 0; }

/** @brief Return active board row count (0 if no game). */
EMSCRIPTEN_KEEPALIVE
int js_status_rows() { return g_game ? g_game->getRows() : 0; }

/** @brief Return total mine count (0 if no game). */
EMSCRIPTEN_KEEPALIVE
int js_status_mines_total() { return g_game ? g_game->getMinesTotal() : 0; }

/** @brief Return number of currently placed flags. */
EMSCRIPTEN_KEEPALIVE
int js_status_flags() { return g_game ? g_game->getFlagsCount() : 0; }

/** @brief Return revealed safe cell count. */
EMSCRIPTEN_KEEPALIVE
int js_status_revealed() { return g_game ? g_game->getRevealedCount() : 0; }

/**
 * @brief Return current game state code.
 * @return 0 = Playing, 1 = Won, 2 = Lost, -1 = No active game.
 */
EMSCRIPTEN_KEEPALIVE
int js_status_state() { return g_game ? g_game->getStateValue() : -1; }
} // extern "C"
