#include "Expression.hpp"

#include <cmath>

enum Function{x, y, sinus, cosinus, average, product};

Expression::Expression()
{
    expression = "0";
    maxDepth = 0;
}

Expression::Expression(std::size_t maxDepth, 
                       unsigned int seed)
{
    Expression::maxDepth = maxDepth;

    if(maxDepth == 0)
    {
        expression = "0";
        return;
    }

    srand(seed);

    std::stack<char> expressionGen;
    std::stack<std::string> infixExpr;
    Function fct;
    unsigned leftOperands = 1, nbOperands = 0, randomNumber; 

    while(leftOperands > 0)
    {
        if(nbOperands + 1 >= maxDepth)
            fct = static_cast<Function>(rand() % 2);
        
        else
        {
            randomNumber = rand() % 300;

            if(randomNumber < 1)
                fct = x;

            if(randomNumber >= 1 && randomNumber < 2)
                fct = y;
            
            if(randomNumber >= 2 && randomNumber < 75)
                fct = sinus;

            if(randomNumber >= 75 && randomNumber < 149)
                fct = cosinus;
            
            if(randomNumber >= 149 && randomNumber < 223)
                fct = average;
            
            if(randomNumber >= 223)
                fct = product;
        }

        switch(fct)
        {
            case x:
                expressionGen.push('x');
                --leftOperands;
                ++nbOperands;
                break;
            
            case y:
                expressionGen.push('y');
                --leftOperands;
                ++nbOperands;
                break;
            
            case sinus:
                expressionGen.push('s');
                ++nbOperands;
                break;

            case cosinus:
                expressionGen.push('c');
                ++nbOperands;
                break;
            
            case average:
                expressionGen.push('a');
                ++leftOperands;
                ++nbOperands;
                break;
            
            case product:
                expressionGen.push('*');
                ++leftOperands;
                ++nbOperands;
                break;

            default:
                break;
        }
    }

    expression = "";

    while(!expressionGen.empty())
    {
        expression += expressionGen.top();
        expressionGen.pop();
    }
    
}

double Expression::evaluateExpression(double x, double y)
{
    double firstValue, secondValue;
    std::stack<double> expressionEval;

    for(char const &c : expression) 
    {
        switch(c)
        {
            case '0':
                expressionEval.push(0.0);
                break;
            case 'x':
                expressionEval.push(x);
                break;
            case 'y':
                expressionEval.push(y);
                break;
            case 's':
                firstValue = expressionEval.top();
                expressionEval.pop();
                expressionEval.push(sin(M_PI * firstValue));
                break;
            case 'c':
                firstValue = expressionEval.top();
                expressionEval.pop();
                expressionEval.push(cos(M_PI * firstValue));
                break;
            case '*':
                firstValue = expressionEval.top();
                expressionEval.pop();
                secondValue = expressionEval.top();
                expressionEval.pop();
                expressionEval.push(firstValue * secondValue);
                break;
            case 'a':
                firstValue = expressionEval.top();
                expressionEval.pop();
                secondValue = expressionEval.top();
                expressionEval.pop();
                expressionEval.push((firstValue + secondValue) / 2);
                break;
            default:
                break;
        }
    }

    firstValue = expressionEval.top();
    expressionEval.pop();

    return firstValue;
}

std::string Expression::getExpression() const
{
    return expression;
}

std::istream& operator>>(std::istream &in, Expression& exp)
{
    in >> exp.expression;

    exp.computeDepth();

    return in;
}

void Expression::computeDepth()
{
    std::stack<std::string> infixExpr;

    std::string firstValue, secondValue;

    if(expression == "0")
    {
        maxDepth = 0;
        return;
    }

    for(char const &c : expression) 
    {
        if(c == 'x' || c == 'y')
            infixExpr.push("()");
            
        if(c == 's' || c == 'c')
        {
            firstValue = infixExpr.top();
            infixExpr.pop();
            infixExpr.push("(" + firstValue + ")");
        }
        if(c == '*' || c == 'a')
        {
            firstValue = infixExpr.top();
            infixExpr.pop();
            secondValue = infixExpr.top();
            infixExpr.pop();
            infixExpr.push("(" + firstValue + secondValue + ")");
        }        
    }

    firstValue = infixExpr.top();
    infixExpr.pop();

    std::size_t depth = 0, currentDepth = 0;

    for(char const &c : firstValue)
    {
        if(c == '(')
            ++currentDepth;
        
        if(c == ')')
        {
            if(currentDepth > depth)
                depth = currentDepth;
            --currentDepth;
        }
    }

    maxDepth = depth;
}

std::size_t Expression::getMaxDepth() const
{
    return maxDepth;
}

void Expression::setMaxDepth(std::size_t depth)
{
    maxDepth = depth;
}
