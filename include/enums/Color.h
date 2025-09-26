#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <ostream>

/**
 * @brief ANSI color codes for terminal text formatting in minesweeper
 *
 * Provides a set of colors used to display numbered cells in the minesweeper game.
 * Each number (1-8) representing nearby mine count has its own distinct color
 * following traditional minesweeper color schemes.
 */
enum class Color
{
    /**
     * @brief Standard blue color
     * Used for displaying the number 1 in cells
     */
    Blue,

    /**
     * @brief Standard green color
     * Used for displaying the number 2 in cells
     */
    Green,

    /**
     * @brief Standard red color
     * Used for displaying the number 3 in cells
     */
    Red,

    /**
     * @brief Bold navy blue color
     * Used for displaying the number 4 in cells
     */
    Navy,

    /**
     * @brief Bold maroon/dark red color
     * Used for displaying the number 5 in cells
     */
    Maroon,

    /**
     * @brief Teal/cyan color
     * Used for displaying the number 6 in cells
     */
    Teal,

    /**
     * @brief Black color
     * Used for displaying the number 7 in cells
     */
    Black,

    /**
     * @brief Gray color
     * Used for displaying the number 8 in cells
     */
    Gray,

    /**
     * @brief Yellow color
     * Used for warnings, highlights, or special displays
     */
    Yellow,

    /**
     * @brief Reset color to terminal default
     * Used to clear any color formatting
     */
    Reset
};

/**
 * @brief Converts a Color enum value to its corresponding ANSI escape sequence
 *
 * @param c The color to convert
 * @return std::string ANSI escape sequence for the specified color
 *
 * @note Returns empty string for invalid/unknown colors
 */
inline std::string toAnsi(Color c)
{
#ifdef NO_ANSI_COLORS
    // In web or environments without ANSI support, return empty sequences
    (void)c;
    return "";
#else
    switch (c)
    {
    case Color::Blue:
        return "\033[34m"; // Blue text
    case Color::Green:
        return "\033[32m"; // Green text
    case Color::Red:
        return "\033[31m"; // Red text
    case Color::Navy:
        return "\033[34;1m"; // Bold blue text
    case Color::Maroon:
        return "\033[31;1m"; // Bold red text
    case Color::Teal:
        return "\033[36m"; // Cyan text
    case Color::Black:
        return "\033[30m"; // Black text
    case Color::Gray:
        return "\033[90m"; // Bright black (gray) text
    case Color::Yellow:
        return "\033[33m"; // Yellow text
    case Color::Reset:
        return "\033[0m"; // Reset all formatting
    default:
        return ""; // No formatting for unknown colors
    }
#endif
}

/**
 * @brief Maps mine count numbers (1-8) to their traditional minesweeper colors
 *
 * @param n The number of adjacent mines (expected range: 1-8)
 * @return Color The corresponding color for the number
 *
 * @note Returns Color::Reset for numbers outside the valid range (1-8)
 *
 * Color mapping follows traditional minesweeper conventions:
 * - 1: Blue
 * - 2: Green
 * - 3: Red
 * - 4: Navy (bold blue)
 * - 5: Maroon (bold red)
 * - 6: Teal
 * - 7: Black
 * - 8: Gray
 */
inline Color colorForNumber(int n)
{
    switch (n)
    {
    case 1:
        return Color::Blue;
    case 2:
        return Color::Green;
    case 3:
        return Color::Red;
    case 4:
        return Color::Navy;
    case 5:
        return Color::Maroon;
    case 6:
        return Color::Teal;
    case 7:
        return Color::Black;
    case 8:
        return Color::Gray;
    default:
        return Color::Reset;
    }
}

/**
 * @brief Stream insertion operator for Color enum
 *
 * Allows direct output of Color values to streams (like std::cout).
 * Automatically converts the color to its ANSI escape sequence.
 *
 * @param os Output stream to write to
 * @param c Color to output
 * @return std::ostream& Reference to the output stream for chaining
 *
 * @code
 * std::cout << Color::Red << "This text is red" << Color::Reset << std::endl;
 * std::cout << Color::Yellow << "This text is yellow" << Color::Reset << std::endl;
 * @endcode
 */
inline std::ostream &operator<<(std::ostream &os, Color c)
{
    return os << toAnsi(c);
}

#endif