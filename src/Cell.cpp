/**
 * @file Cell.cpp
 * @brief Implementation of Cell class methods
 * @author ayrto
 * @date 06/06/2025
 */

#include "Cell.h"

// Constructor - initializes cell with content and state
Cell::Cell(CellContent content, CellState state) : content(content), state(state) {}

// * Getters
CellContent Cell::getContent() const { return content; }
int Cell::getNearbyMines() const { return nearbyMines; }
CellState Cell::getState() const { return state; }

// State check methods - compare against enum values
bool Cell::isHidden() const { return state == CellState::Hidden; }
bool Cell::isRevealed() const { return state == CellState::Revealed; }
bool Cell::isFlagged() const { return state == CellState::Flagged; }

// Content check methods - compare against enum values
bool Cell::isMine() const { return content == CellContent::Mine; }
bool Cell::isNumber() const { return content == CellContent::Number; }
bool Cell::isEmpty() const { return content == CellContent::Empty; }

// * Setters -
void Cell::setContent(CellContent c) { content = c; }
void Cell::setNearbyMines(int mines) { nearbyMines = mines; }
void Cell::setState(CellState s) { state = s; }

// * Utils
void Cell::toggleFlag() { state = isFlagged() ? CellState::Hidden : CellState::Flagged; }