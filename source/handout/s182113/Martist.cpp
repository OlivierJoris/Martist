#include "Martist.hpp"

Martist::Martist(std::uint8_t *buffer, std::size_t width,
                 std::size_t height, std::size_t redDepth,
                 std::size_t greenDepth, std::size_t blueDepth)
{
    if(!buffer)
        throw std::invalid_argument("Error : buffer is NULL !\n");

    Martist::buffer = buffer;
    
    if(width <= 0)
        throw std::invalid_argument("Error : width is smaller than 0 !\n");
    
    Martist::width = width;
    
    if(height <= 0)
        throw std::invalid_argument("Error : height is smaller than 0 !\n");

    Martist::height = height;

    srand(time(NULL));

    redSeed = rand();
    greenSeed = rand();
    blueSeed = rand();

    redExpression.setMaxDepth(redDepth);
    greenExpression.setMaxDepth(greenDepth);
    blueExpression.setMaxDepth(blueDepth);
}

void Martist::redDepth(std::size_t depth)
{
    redExpression.setMaxDepth(depth);
}

void Martist::greenDepth(std::size_t depth)
{
    greenExpression.setMaxDepth(depth);
}

void Martist::blueDepth(std::size_t depth)
{
   blueExpression.setMaxDepth(depth);
}

std::size_t Martist::redDepth() const
{
    return redExpression.getMaxDepth();
}

std::size_t Martist::greenDepth() const
{
    return greenExpression.getMaxDepth();
}

std::size_t Martist::blueDepth() const
{
    return blueExpression.getMaxDepth();
}

void Martist::changeBuffer(std::uint8_t* buffer, std::size_t width,
                           std::size_t height)
{
    if(!buffer)
        throw std::invalid_argument("Error : buffer is NULL !\n");
    
    Martist::buffer = buffer;
    
    if(width <= 0)
        throw std::invalid_argument("Error : width is smaller than 0 !\n");
    
    Martist::width = width;
    
    if(height <= 0)
        throw std::invalid_argument("Error : height is smaller than 0 !\n");

    Martist::height = height;
}

void Martist::paint()
{  
    redExpression = Expression(redExpression.getMaxDepth(), redSeed);
    greenExpression = Expression(greenExpression.getMaxDepth(), greenSeed);
    blueExpression = Expression(blueExpression.getMaxDepth(), blueSeed);

    loadBuffer();

    seed(rand());
}

void Martist::seed(unsigned int seed)
{
    srand(seed);

    redSeed = rand();
    greenSeed = rand();
    blueSeed = rand();
}

std::istream& operator>>(std::istream &in, Martist& martist)
{
    in >> martist.redExpression;

    in >> martist.greenExpression;

    in >> martist.blueExpression;

    martist.loadBuffer();

    return in;
}

std::ostream& operator<<(std::ostream &out, const Martist& martist)
{
    out << martist.redExpression.getExpression() << '\n' <<
           martist.greenExpression.getExpression() << '\n' <<
           martist.blueExpression.getExpression() << '\n';

    return out;
}

void Martist::loadBuffer()
{
    std::size_t pixelNb;
    double x, y;
    int value;

    for(std::size_t i = 0; i < height * width * 3; )
    {
        pixelNb = i / 3;

        x = (int) ((pixelNb % width) - (width / 2));
        y = (int) ((height / 2) - (pixelNb / width));

        x += 0.5;
        y -= 0.5;

        x /= (width / 2);
        y /= (height / 2);

        value = (127 * redExpression.evaluateExpression(x, y));
        if(value >= 0) 
            buffer[i] = value + 128;
        
        if(value < 0)
            buffer[i] = value + 127;
        
        if(redExpression.getExpression() == "0")
            buffer[i] = 0;
        ++i;

        value = (127 * greenExpression.evaluateExpression(x, y));
        if(value >= 0) 
            buffer[i] = value + 128;
        
        if(value < 0)
            buffer[i] = value + 127;
        
        if(greenExpression.getExpression() == "0")
            buffer[i] = 0;
        ++i;

        value = (127 * blueExpression.evaluateExpression(x, y));
        if(value >= 0) 
            buffer[i] = value + 128;
        
        if(value < 0)
            buffer[i] = value + 127;
        
        if(blueExpression.getExpression() == "0")
            buffer[i] = 0;
        ++i;
    }
}
