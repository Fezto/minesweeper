/**
 * @file Game.cpp
 * @brief Implementation of Game class methods for minesweeper game logic
 * @author ayrto
 * @date 07/06/2025
 */

#include "Game.h"
#include "enums/Color.h"
#include "Message.h"

#include <iostream>
#include <regex>
#include <cctype>

// Constructor - initializes game with board dimensions and mine count
Game::Game(int columns, int rows, int mines) : board(columns, rows, mines)
{
}

// Main game loop - handles input, validation, and game flow
void Game::start()
{
    clear();

    while (isPlaying())
    {
        board.print();

        std::string input = prompt();

        if (!isValidInput(input))
        {
            clear();
            Message::warn("Formato inválido!");
            continue;
        }

        auto [column, row, action] = parseInput(input);
        play(column, row, action);
        checkWinCondition();
        clear();
    }

    board.print();

    Message::warn(isLost() ? "Has perdido el juego!" : "Has ganado el juego!");

    std::cin.get();
}

// Win condition check - counts revealed non-mine cells
void Game::checkWinCondition()
{
    int cellsWithoutMine = board.getColumns() * board.getRows() - board.getMines();
    int revealedCellsWithoutMine = 0;

    for (std::vector<Cell> &row : board.getBoard())
    {
        for (Cell &cell : row)
        {
            if (!cell.isMine() && cell.isRevealed())
                ++revealedCellsWithoutMine;
        }
    }

    if (cellsWithoutMine == revealedCellsWithoutMine)
        setWon();
}

// User input prompt - displays colorized instructions and gets input
std::string Game::prompt()
{
    std::cout << std::endl;
    std::cout << "+--------------------------------------------------------------+\n";
    std::cout << "| Escoge una columna (" << Color::Yellow << "A" << Color::Reset << "), una fila (" << Color::Yellow << "1" << Color::Reset << ") y tu accion (" << Color::Red << "F" << Color::Reset << ", " << Color::Teal << "R" << Color::Reset << ")      |\n";
    std::cout << "| - " << Color::Red << "F" << Color::Reset << " es de " << Color::Red << "Flag" << Color::Reset << " y sirve para marcar una celda con una bandera |\n";
    std::cout << "| - " << Color::Teal << "R" << Color::Reset << " es de " << Color::Teal << "Reveal" << Color::Reset << " y sirve para descubrir una celda            |\n";
    std::cout << "| - Si quieres revelar, puedes omitir por completo la " << Color::Teal << "R" << Color::Reset << "        |\n";
    std::cout << "|                                                              |\n";
    std::cout << "| Entradas validas de ejemplo: (A9 F), (B3 R), (C4) etc.       |\n";
    std::cout << "+--------------------------------------------------------------+\n";

    std::string input;
    std::cout << "\n -> ";
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    return input;
}

// Process player move - handles flag/reveal actions
void Game::play(int column, int row, char action)
{
    Cell &cell = board.getCell(column, row);

    if (action == 'F')
    {
        if (!cell.isRevealed())
        {
            cell.toggleFlag();
        }
        return;
    }

    revealCellAndPropagate(column, row);

    if (cell.isMine())
    {
        setLost();
        return;
    }
}

// Flood-fill algorithm - reveals cells and propagates to empty neighbors
void Game::revealCellAndPropagate(int column, int row)
{
    if (!board.isValidBoardCoordinate(column, row))
        return;

    Cell &cell = board.getCell(column, row);

    if (cell.isRevealed() || cell.isFlagged())
        return;

    cell.setState(CellState::Revealed);

    if (cell.isEmpty())
    {
        for (int r = -1; r <= 1; ++r)
        {
            for (int c = -1; c <= 1; ++c)
            {
                if (!board.isValidBoardCoordinate(column + c, row + r))
                    continue;

                if (c == 0 && r == 0)
                    continue;

                Cell &neighborCell = board.getCell(column + c, row + r);

                if (!neighborCell.isRevealed() && !neighborCell.isFlagged())
                {
                    revealCellAndPropagate(column + c, row + r);
                }
            }
        }
    }
}

// * Getters - simple state check methods
bool Game::isPlaying() const { return state == GameState::Playing; }
bool Game::isWon() const { return state == GameState::Won; }
bool Game::isLost() const { return state == GameState::Lost; }

// * Setters - direct state assignment
void Game::setWon() { state = GameState::Won; }
void Game::setLost() { state = GameState::Lost; }

// * Utils - utility methods for game operations
void Game::print() const { board.print(); }

// Input validation using regex pattern matching
bool Game::isValidInput(const std::string &input) const
{
    std::regex promptValidation(R"(([A-Z])(1?[0-9]|2[0-6])(\s([FR]))?)");
    return std::regex_match(input, promptValidation);
}

// Parse user input into structured data (column, row, action)
InputData Game::parseInput(const std::string &input) const
{
    int playedColumn = static_cast<int>(input.at(0)) - 65;
    int spacePos = input.find(' ');
    int playedRow;
    char action;

    if (spacePos == std::string::npos)
    {
        playedRow = std::stoi(input.substr(1)) - 1;
        action = 'R';
    }
    else
    {
        playedRow = std::stoi(input.substr(1, spacePos - 1)) - 1;
        action = input.at(input.length() - 1);
    }

    return {playedColumn, playedRow, action};
}

// Cross-platform screen clearing
void Game::clear()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}
