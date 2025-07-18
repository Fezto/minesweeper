//
// Created by ayrto on 10/06/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @brief Represents the current state of the minesweeper game
 * 
 * Defines the possible states that a minesweeper game can be in during
 * its lifecycle. Used to control game flow and determine when the game
 * should end and what message to display to the player.
 */
enum class GameState
{
    /**
     * @brief Game is currently active and ongoing
     * 
     * The player can continue making moves (revealing cells, placing flags).
     * This is the default state when a new game starts.
     */
    Playing,
    
    /**
     * @brief Player has successfully won the game
     * 
     * All non-mine cells have been revealed without hitting any mines.
     * The game loop should terminate and display a victory message.
     */
    Won,
    
    /**
     * @brief Player has lost the game
     * 
     * The player revealed a cell containing a mine.
     * The game loop should terminate and display a defeat message.
     */
    Lost
};

#endif // GAMESTATE_H