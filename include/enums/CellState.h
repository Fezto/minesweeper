//
// Created by ayrto on 07/06/2025.
//

#ifndef CELLSTATE_H
#define CELLSTATE_H

/**
 * @brief Represents the visual state of a cell in the minesweeper game
 *
 * Defines the different states a cell can be in from the player's perspective.
 * Each state has an associated character value used for terminal display.
 * The underlying type is char to directly map to display characters.
 */
enum class CellState : char
{
    /**
     * @brief Cell is hidden from the player
     *
     * The cell hasn't been revealed yet and shows as '#' in the terminal.
     * This is the default state for all cells at game start.
     */
    Hidden = '#',

    /**
     * @brief Cell has been revealed by the player
     *
     * The cell's content (empty, number, or mine) is visible to the player.
     * Displays as a space character when the cell content is shown.
     */
    Revealed = ' ',

    /**
     * @brief Cell has been flagged by the player
     *
     * Player has marked this cell as potentially containing a mine.
     * Displays as 'F' in the terminal. Flagged cells cannot be revealed
     * until the flag is removed.
     */
    Flagged = 'F'
};

#endif // CELLSTATE_H