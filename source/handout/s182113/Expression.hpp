#ifndef EXPRESSION_HH
#define EXPRESSION_HH

#include <iostream>
#include <vector>
#include <stack>

/* -------------------------------------------------------------------------*
 * Class representing an expression.
 * -------------------------------------------------------------------------*/
class Expression
{
    public:
        /* -----------------------------------------------------------------*
         * Default constructor.
         * -----------------------------------------------------------------*/
        Expression();

         /* -----------------------------------------------------------------*
         * Constructor.
         * 
         * PARAMETERS
         * maxDepth   The maximum allowed depth of the expression.
         * seed       Seed of the expression generation.
         * -----------------------------------------------------------------*/
        Expression(std::size_t maxDepth, unsigned int seed);

         /* -----------------------------------------------------------------*
         * Evaluates the current expression for given values of x and y.
         * 
         * PARAMETERS
         * x   The x value.
         * y   The y value.
         * 
         * RETURN
         * The evaluation of the expression for the given values of x and y.
         * -----------------------------------------------------------------*/
        double evaluateExpression(double x, double y);

         /* -----------------------------------------------------------------*
         * Gets the string representation of the current expression.
         * 
         * RETURN
         * The string representation of the current expression.
         * -----------------------------------------------------------------*/
        std::string getExpression() const;

         /* -----------------------------------------------------------------*
         * Computes the depth of the current expression and updates it.
         * -----------------------------------------------------------------*/
        void computeDepth();

        /* -----------------------------------------------------------------*
         * Gets the maximum depth of the current expression.
         * 
         * RETURN
         * The depth of the current expression.
         * -----------------------------------------------------------------*/
        std::size_t getMaxDepth() const;

        /* -----------------------------------------------------------------*
         * Sets the maximum depth to a given value.
         * 
         * PARAMETERS
         * maxDepth   New maximum depth that is set.
         * -----------------------------------------------------------------*/
        void setMaxDepth(std::size_t maxDepth);

        /* -----------------------------------------------------------------*
         * Reads an image spec from a stream and update the expression and its
         * depth.
         * 
         * PARAMETERS
         * in           The input stream.
         * expression   The written expression.
         * 
         * RETURN
         * The input stream with that has been read.
         * -----------------------------------------------------------------*/
        friend std::istream& operator>>(std::istream &in, 
                                        Expression& expression);

    private:
        std::string expression;
        std::size_t maxDepth;
};

#endif
