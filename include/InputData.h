/**
 * @brief Represents parsed user input for a minesweeper game move
 *
 * This structure holds the processed data from user input after validation
 * and parsing. It contains the board coordinates and the action to perform
 * on the specified cell.
 */
struct InputData
{
    /**
     * @brief Column index on the board (0-based)
     *
     * Represents the horizontal position on the game board.
     * Corresponds to letters A-Z in user input, converted to 0-based index.
     *
     * @note Range: 0 to (board_width - 1)
     */
    int column;

    /**
     * @brief Row index on the board (0-based)
     *
     * Represents the vertical position on the game board.
     * Corresponds to numbers 1-26 in user input, converted to 0-based index.
     *
     * @note Range: 0 to (board_height - 1)
     */
    int row;

    /**
     * @brief Action to perform on the specified cell
     *
     * Defines what operation to execute on the cell at the given coordinates.
     * - 'R': Reveal the cell (default action if not specified)
     * - 'F': Toggle flag on the cell
     *
     * @note Valid values: 'R' (reveal) or 'F' (flag)
     */
    char action;
};