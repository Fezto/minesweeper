//
// Created by ayrto on 06/06/2025.
//

#ifndef CELLCONTENT_H
#define CELLCONTENT_H

/**
 * @brief Represents the content type of a cell in the minesweeper board
 *
 * Defines the different types of content that a cell can contain
 * in the minesweeper game. Used to determine how the cell should
 * be displayed and how it behaves when revealed.
 */
enum class CellContent
{
    /**
     * @brief Empty cell with no adjacent mines
     *
     * Indicates that the cell doesn't contain a mine and has
     * no mines in adjacent cells (value 0).
     */
    Empty,

    /**
     * @brief Cell containing a number indicating nearby mines
     *
     * The cell contains a number from 1-8 that represents
     * the count of mines in adjacent cells.
     */
    Number,

    /**
     * @brief Cell containing a mine
     *
     * Indicates that this cell contains a mine.
     * If the player reveals it, the game is lost!
     */
    Mine
};

#endif // CELLCONTENT_H