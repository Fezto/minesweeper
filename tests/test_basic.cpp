#include <cassert>
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Cell.h"

// Test básico para verificar la creación del tablero
void testBoardCreation()
{
    Board board(10, 8, 10);

    // Verificar dimensiones
    assert(board.getColumns() == 10);
    assert(board.getRows() == 8);
    assert(board.getMines() == 10);

    std::cout << "✅ Test de creación del tablero pasado\n";
}

// Test para verificar coordenadas válidas
void testValidCoordinates()
{
    Board board(5, 5, 5);

    // Coordenadas válidas
    assert(board.isValidBoardCoordinate(0, 0) == true);
    assert(board.isValidBoardCoordinate(4, 4) == true);
    assert(board.isValidBoardCoordinate(2, 3) == true);

    // Coordenadas inválidas
    assert(board.isValidBoardCoordinate(-1, 0) == false);
    assert(board.isValidBoardCoordinate(0, -1) == false);
    assert(board.isValidBoardCoordinate(5, 0) == false);
    assert(board.isValidBoardCoordinate(0, 5) == false);

    std::cout << "✅ Test de coordenadas válidas pasado\n";
}

// Test para verificar estados de celda
void testCellStates()
{
    Cell cell(CellContent::Empty);

    // Estado inicial
    assert(cell.isHidden() == true);
    assert(cell.isRevealed() == false);
    assert(cell.isFlagged() == false);

    // Cambiar estado a bandera
    cell.toggleFlag();
    assert(cell.isFlagged() == true);
    assert(cell.isHidden() == false);

    // Quitar bandera
    cell.toggleFlag();
    assert(cell.isFlagged() == false);
    assert(cell.isHidden() == true);

    // Revelar celda
    cell.setState(CellState::Revealed);
    assert(cell.isRevealed() == true);
    assert(cell.isHidden() == false);

    std::cout << "✅ Test de estados de celda pasado\n";
}

// Test para verificar contenido de celda
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

    std::cout << "✅ Test de contenido de celda pasado\n";
}

// Test para verificar el conteo de minas cercanas
void testMineCount()
{
    Cell cell(CellContent::Number);

    // Establecer número de minas cercanas
    cell.setNearbyMines(3);
    assert(cell.getNearbyMines() == 3);

    cell.setNearbyMines(0);
    assert(cell.getNearbyMines() == 0);

    cell.setNearbyMines(8);
    assert(cell.getNearbyMines() == 8);

    std::cout << "✅ Test de conteo de minas pasado\n";
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
