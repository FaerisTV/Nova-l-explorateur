/**
 * @file piece.cpp
 * @brief Implementation of the Piece class methods.
 */

#include "piece.h"

/**
 * @brief Constructor for Piece class.
 * @param aX The x-coordinate of the piece.
 * @param aY The y-coordinate of the piece.
 * @param aWidth The width of the piece.
 * @param aHeight The height of the piece.
 */
Piece::Piece(int aX, int aY, int aWidth, int aHeight)
    : itsPiece(aX, aY, aWidth, aHeight)
{}

/**
 * @brief Returns the rectangle representing the piece's dimensions and position.
 * @return QRect object representing the piece's rectangle.
 */
QRect Piece::getRect()
{
    return itsPiece;
}
