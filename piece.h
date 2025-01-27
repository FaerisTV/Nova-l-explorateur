#ifndef PIECE_H
#define PIECE_H

#include <QRect>

/**
 * @brief The Piece class represents a collectible piece in the game.
 */
class Piece
{
    QRect itsPiece; /**< Rectangle representing the piece's position and size. */

public:
    /**
     * @brief Constructor to initialize a collectible piece.
     *
     * @param aX Initial X position of the piece
     * @param aY Initial Y position of the piece
     * @param aWidth Width of the piece
     * @param aHeight Height of the piece
     */
    Piece(int aX, int aY, int aWidth, int aHeight);

    /**
     * @brief Gets the rectangle representing the collectible piece.
     *
     * @return QRect object representing the piece's position and size
     */
    QRect getRect();
};

#endif // PIECE_H
