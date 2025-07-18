/**
 * @file Board.cpp
 * @brief Implementation of the Board class for the Minesweeper game
 * @author ayrto
 * @date 2025
 */

#include "Board.h"

#include <iomanip>
#include <iostream>
#include <random>

#include "enums/CellContent.h"
#include "Game.h"
#include "enums/Color.h"

Board::Board(int columns, int rows, int mines) : columns(columns), rows(rows), mines(mines)
{
    // C++17 Class Template Argument Deduction! (CTAD)
    board = std::vector(rows, std::vector(columns, Cell(CellContent::Empty)));
    setMines();
    setNumber();
}

// * Getters
int Board::getColumns() const { return columns; }
int Board::getRows() const { return rows; }
Cell Board::getCell(int column, int row) const { return board[row][column]; }
Cell &Board::getCell(int column, int row) { return board[row][column]; }
CellContent Board::getCellContent(int column, int row) const { return getCell(column, row).getContent(); }
std::vector<std::vector<Cell>> Board::getBoard() const { return board; }
int Board::getMines() const { return mines; }

// * Setters
void Board::setCellContent(int column, int row, CellContent content) { getCell(column, row).setContent(content); }

void Board::setMines()
{
    int includedMines = 0;

    while (includedMines < mines)
    {
        // C++17 structured bindings for more beautiful and cleaner code
        const auto [column, row] = generateRandomCoordinates();

        Cell &cell = getCell(column, row);
        if (!cell.isMine())
        {
            cell.setContent(CellContent::Mine);
            ++includedMines;
        }
    }
}

void Board::setNumber()
{
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < columns; ++c)
        {
            Cell &cell = getCell(c, r);

            if (cell.isMine())
                continue;

            int mines = calculateNearbyMines(c, r);

            if (mines > 0)
            {
                cell.setContent(CellContent::Number);
            }

            cell.setNearbyMines(mines);
        }
    }
}

// * Utils
int Board::calculateNearbyMines(int column, int row)
{
    if (!isValidBoardCoordinate(column, row))
        return 0;

    int mines{0};

    // Check all 8 adjacent cells (3x3 grid minus center)
    for (int r = -1; r <= 1; ++r)
    {
        for (int c = -1; c <= 1; ++c)
        {
            if (!isValidBoardCoordinate(column + c, row + r))
                continue;

            if (c == 0 && r == 0) // Skip center cell. It is unnecesary!
                continue;

            Cell &cell = getCell(column + c, row + r);

            if (cell.isMine())
            {
                ++mines;
            }
        }
    }
    return mines;
}

bool Board::isValidBoardCoordinate(int column, int row) const
{
    return row >= 0 && row < rows && column >= 0 && column < columns;
}

void Board::print() const
{
    // Board rendering with borders and labels
    const int drawColumns = columns + 3;
    const int drawRows = rows + 3;

    for (int r = 0; r < drawRows; ++r)
    {
        for (int c = 0; c < drawColumns; ++c)
        {
            // Column headers (A, B, C, ...)
            if (r == 0 && c > 1 && c < drawColumns - 1)
            {
                std::cout << Color::Yellow << " " << static_cast<char>(c + 63) << Color::Reset << " ";
            }
            // Row numbers (1, 2, 3, ...)
            else if (c == 0 && r > 1 && r < drawRows - 1)
            {
                std::cout << Color::Yellow << std::setw(2) << r - 1 << Color::Reset << " ";
            }
            // Border corners
            else if ((r == 1 || r == drawRows - 1) && (c == 1 || c == drawColumns - 1))
            {
                std::cout << "+";
            }
            // Horizontal borders
            else if (r == 1 || r == drawRows - 1)
            {
                std::cout << " - ";
            }
            // Vertical borders
            else if (c == 1 || c == drawColumns - 1)
            {
                std::cout << "|";
            }
            // Game cells
            else
            {
                int innerRow = r - 2;
                int innerColumn = c - 2;

                if (isValidBoardCoordinate(innerColumn, innerRow))
                {
                    Cell cell = getCell(innerColumn, innerRow);

                    if (cell.isHidden())
                    {
                        std::cout << " # ";
                        continue;
                    }

                    if (cell.isFlagged())
                    {
                        std::cout << Color::Red << " F " << Color::Reset;
                        continue;
                    }

                    if (cell.getContent() == CellContent::Mine)
                    {
                        std::cout << " * ";
                        continue;
                    }

                    if (cell.getContent() == CellContent::Number && cell.getNearbyMines() > 0)
                    {
                        Color mineColor = colorForNumber(cell.getNearbyMines());
                        std::cout << " " << mineColor << cell.getNearbyMines() << Color::Reset << " ";
                    }
                    else
                    {
                        std::cout << "   ";
                    }
                }
                else
                {
                    std::cout << "   ";
                }
            }
        }
        std::cout << "\n";
    }
}

std::array<int, 2> Board::generateRandomCoordinates() const
{
    // Modern C++ random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution distRow(0, rows - 1);
    std::uniform_int_distribution distColumn(0, columns - 1);

    return {distColumn(gen), distRow(gen)};
}