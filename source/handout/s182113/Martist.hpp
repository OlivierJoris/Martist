#ifndef MARTIST_HH
#define MARTIST_HH

#include "Expression.hpp"

#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------*
 * Martist class as defined in the statement.
 * -------------------------------------------------------------------------*/
class Martist
{
    public:
        /* -----------------------------------------------------------------*
         * Constructor.
         * 
         * PARAMETERS
         * buffer      Buffer of row first pixels (red, blue, and green in 
         *             this order).
         * width       Width of the image.
         * height      Height of the image.
         * redDepth    Maximum allowed depth for the red expression.
         * greenDepth  Maximum allowed depth for the green expression.
         * blueDepth   Maximum allowed depth for the blue expression.
         * -----------------------------------------------------------------*/
        Martist(std::uint8_t *buffer, std::size_t width,
                std::size_t height, std::size_t redDepth,
                std::size_t greenDepth, std::size_t blueDepth);
        
         /* -----------------------------------------------------------------*
         * Sets the maximum allowed depth of the red expression to the given 
         * value.
         * 
         * PARAMETERS
         * depth   The given new depth.
         * -----------------------------------------------------------------*/
        void redDepth(std::size_t depth);

         /* -----------------------------------------------------------------*
         * Sets the maximum allowed depth of the green expression to the given 
         * value.
         * 
         * PARAMETERS
         * depth   The given new depth.
         * -----------------------------------------------------------------*/
        void greenDepth(std::size_t depth);

        /* -----------------------------------------------------------------*
         * Sets the maximum allowed depth of the blue expression to the given 
         * value.
         * 
         * PARAMETERS
         * depth   The given new depth.
         * -----------------------------------------------------------------*/
        void blueDepth(std::size_t depth);

        /* -----------------------------------------------------------------*
         * Gets the maximum allowed depth of the red expression.
         * 
         * RETURN
         * The depth of the red expression.
         * -----------------------------------------------------------------*/
        std::size_t redDepth() const;

        /* -----------------------------------------------------------------*
         * Gets the maximum allowed depth of the green expression.
         * 
         * RETURN
         * The depth of the red expression.
         * -----------------------------------------------------------------*/
        std::size_t greenDepth() const;

        /* -----------------------------------------------------------------*
         * Gets the maximum allowed depth of the blue expression.
         * 
         * RETURN
         * The depth of the red expression.
         * -----------------------------------------------------------------*/
        std::size_t blueDepth() const;

        /* -----------------------------------------------------------------*
         * Updates the buffer and the image size.
         * 
         * PARAMETERS
         * buffer   The new buffer.
         * width    The new width.
         * height   The new height.
         * -----------------------------------------------------------------*/
        void changeBuffer(std::uint8_t* buffer, std::size_t width,
                          std::size_t height);

        /* -----------------------------------------------------------------*
         * Paints the image to the buffer according to the actual 
         * expressions.
         * -----------------------------------------------------------------*/
        void paint();

        /* -----------------------------------------------------------------*
         * Changes the mood of the image.
         * 
         * PARAMETERS
         * seed   Seed that seed the randomness of the image.
         * -----------------------------------------------------------------*/
        void seed(unsigned int seed);

        /* -----------------------------------------------------------------*
         * Read an image spec from a stream and updates the depths of 
         * expressions and redraws the image to the buffer.
         * 
         * PARAMETERS
         * in        The input stream.
         * martist   The written martist.
         * 
         * RETURN
         * The input stream with that has been read.
         * -----------------------------------------------------------------*/
        friend std::istream& operator>>(std::istream &in, Martist& martist);

        /* -----------------------------------------------------------------*
         * Writes the last painted image spec to a stream.
         * 
         * PARAMETERS
         * out       The stream.
         * martist   The martist to write.
         * 
         * RETURN
         * The out stream that has been written.
         * -----------------------------------------------------------------*/
        friend std::ostream& operator<<(std::ostream &out, 
                                        const Martist& martist);

    private:
        /* -----------------------------------------------------------------*
         * Load the image to the buffer.
         * -----------------------------------------------------------------*/
        void loadBuffer();

        std::uint8_t *buffer;
        std::size_t width;
        std::size_t height;
        unsigned int redSeed;
        unsigned int greenSeed;
        unsigned int blueSeed;
        Expression redExpression;
        Expression greenExpression;
        Expression blueExpression;
};

#endif
