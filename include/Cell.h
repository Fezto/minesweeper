//
// Created by ayrto on 06/06/2025.
//

#ifndef CELL_H
#define CELL_H

#include "enums/CellContent.h"
#include "enums/CellState.h"

/**
 * @brief Represents a single cell in the minesweeper board
 *
 * The Cell class encapsulates the state and content of an individual cell
 * in the minesweeper game. Each cell has content (empty, number, or mine),
 * a visual state (hidden, revealed, or flagged), and tracks nearby mine count.
 */
class Cell
{
private:
    // * Properties
    CellContent content; ///< What the cell contains (empty, number, or mine)
    CellState state;     ///< Current visual state (hidden, revealed, or flagged)
    int nearbyMines{0};  ///< Number of mines in adjacent cells (0-8)

public:
    /**
     * @brief Constructs a new Cell with specified content and optional state
     *
     * @param content The content type of the cell (empty, number, or mine)
     * @param state The initial visual state (defaults to Hidden)
     *
     * @note The explicit keyword prevents implicit conversions from CellContent
     */
    explicit Cell(CellContent content, CellState state = CellState::Hidden);

    // * Getters

    /**
     * @brief Gets the content type of the cell
     * @return CellContent The content (empty, number, or mine)
     */
    CellContent getContent() const;

    /**
     * @brief Gets the number of mines in adjacent cells
     * @return int Number of nearby mines (0-8)
     */
    int getNearbyMines() const;

    /**
     * @brief Gets the current visual state of the cell
     * @return CellState The state (hidden, revealed, or flagged)
     */
    CellState getState() const;

    /**
     * @brief Checks if the cell is currently hidden from the player
     * @return bool True if the cell state is Hidden
     */
    bool isHidden() const;

    /**
     * @brief Checks if the cell has been revealed by the player
     * @return bool True if the cell state is Revealed
     */
    bool isRevealed() const;

    /**
     * @brief Checks if the cell has been flagged by the player
     * @return bool True if the cell state is Flagged
     */
    bool isFlagged() const;

    /**
     * @brief Checks if the cell contains a mine
     * @return bool True if the cell content is Mine
     */
    bool isMine() const;

    /**
     * @brief Checks if the cell contains a number (has nearby mines)
     * @return bool True if the cell content is Number
     */
    bool isNumber() const;

    /**
     * @brief Checks if the cell is empty (no nearby mines)
     * @return bool True if the cell content is Empty
     */
    bool isEmpty() const;

    // * Setters

    /**
     * @brief Sets the content type of the cell
     * @param content The new content type (empty, number, or mine)
     */
    void setContent(CellContent content);

    /**
     * @brief Sets the number of nearby mines for this cell
     * @param mines Number of mines in adjacent cells (0-8)
     * @pre mines >= 0 && mines <= 8
     */
    void setNearbyMines(int mines);

    /**
     * @brief Sets the visual state of the cell
     * @param state The new state (hidden, revealed, or flagged)
     */
    void setState(CellState state);

    // * Utils

    /**
     * @brief Toggles the flag state of the cell
     *
     * If the cell is currently flagged, removes the flag (sets to Hidden).
     * If the cell is hidden, adds a flag (sets to Flagged).
     * Has no effect if the cell is already revealed.
     *
     * @note Only works on hidden or flagged cells, not revealed cells
     */
    void toggleFlag();
};

#endif // CELL_H