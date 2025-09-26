#include <cassert>
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Cell.h"

// Basic test to verify board creation
void testBoardCreation()
{
    Board board(10, 8, 10);

    // Verify dimensions
    assert(board.getColumns() == 10);
    assert(board.getRows() == 8);
    assert(board.getMines() == 10);

    std::cout << "\u2705 Board creation test passed\n";
}

// Test to verify valid coordinates
void testValidCoordinates()
{
    Board board(5, 5, 5);

    // Valid coordinates
    assert(board.isValidBoardCoordinate(0, 0) == true);
    assert(board.isValidBoardCoordinate(4, 4) == true);
    assert(board.isValidBoardCoordinate(2, 3) == true);

    // Invalid coordinates
    assert(board.isValidBoardCoordinate(-1, 0) == false);
    assert(board.isValidBoardCoordinate(0, -1) == false);
    assert(board.isValidBoardCoordinate(5, 0) == false);
    assert(board.isValidBoardCoordinate(0, 5) == false);

    std::cout << "\u2705 Valid coordinates test passed\n";
}

// Test to verify cell states
void testCellStates()
{
    Cell cell(CellContent::Empty);

    // Initial state
    assert(cell.isHidden() == true);
    assert(cell.isRevealed() == false);
    assert(cell.isFlagged() == false);

    // Change state to flagged
    cell.toggleFlag();
    assert(cell.isFlagged() == true);
    assert(cell.isHidden() == false);

    // Remove flag
    cell.toggleFlag();
    assert(cell.isFlagged() == false);
    assert(cell.isHidden() == true);

    // Reveal cell
    cell.setState(CellState::Revealed);
    assert(cell.isRevealed() == true);
    assert(cell.isHidden() == false);

    std::cout << "\u2705 Cell state test passed\n";
}

// Test to verify cell content
void testCellContent()
{
    Cell emptyCell(CellContent::Empty);
    Cell mineCell(CellContent::Mine);
    Cell numberCell(CellContent::Number);

    assert(emptyCell.isEmpty() == true);
    assert(emptyCell.isMine() == false);

    assert(mineCell.isMine() == true);
    assert(mineCell.isEmpty() == false);

    assert(numberCell.getContent() == CellContent::Number);

    std::cout << "\u2705 Cell content test passed\n";
}

// Test to verify nearby mine count
void testMineCount()
{
    Cell cell(CellContent::Number);

    // Set number of nearby mines
    cell.setNearbyMines(3);
    assert(cell.getNearbyMines() == 3);

    cell.setNearbyMines(0);
    assert(cell.getNearbyMines() == 0);

    cell.setNearbyMines(8);
    assert(cell.getNearbyMines() == 8);

    std::cout << "\u2705 Mine count test passed\n";
}

int main()
{
    std::cout << "🧪 Ejecutando tests unitarios...\n\n";

    try
    {
        testBoardCreation();
        testValidCoordinates();
        testCellStates();
        testCellContent();
        testMineCount();

        std::cout << "\n✅ ¡Todos los tests pasaron exitosamente!\n";
        std::cout << "🎉 El proyecto está listo para producción.\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "\n❌ Error en los tests: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
