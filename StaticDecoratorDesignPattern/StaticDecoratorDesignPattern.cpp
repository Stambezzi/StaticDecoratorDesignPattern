#include <iostream>
#include <sstream> 
#include <ostream>

class Shape
{
public:
    virtual std::string str() const = 0;
};

class Circle : public Shape
{
public:
    Circle(double radius) : fRadius(radius) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "Circle with a radius of " << fRadius;
        return oss.str();
    }

    void Scale( double scaleFactor )
    {
        fRadius *= scaleFactor;
    }

    friend std::ostream& operator<<( std::ostream& os, const Circle& circle );
private:
    double fRadius;
};

std::ostream& operator<<( std::ostream& os, const Circle& circle )
{
    os << circle.str() << std::endl;
    return os;
}

class Square : public Shape
{
public:
    Square( double side ) : fSide( side ) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "Square with a radius of " << fSide;
        return oss.str();
    }

    friend std::ostream& operator<<( std::ostream& os, const Square& square );
private:
    double fSide;
};

std::ostream& operator<<( std::ostream& os, const Square& square )
{
    os << square.str() << std::endl;
    return os;
}

template <typename T> 
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> class ColoredShape : public T
{
public:
    template <typename...Args>
    ColoredShape( const std::string& color, Args ...args ) 
        : T(std::forward<Args>(args)...), fColor( color ) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A " << fColor << " " << T::str();
        return oss.str();
    }

    friend std::ostream& operator<<( std::ostream& os, const Circle& circle );

private:
    std::string fColor;
};

template <IsAShape T>
std::ostream& operator<<( std::ostream& os, const ColoredShape<T>& coloredShape )
{
    os << coloredShape.str() << std::endl;
    return os;
}

int main()
{
    Circle circ( 5 );
    std::cout << circ;

    Square sqr( 10 );
    std::cout << sqr;

    ColoredShape<Circle> redCirle( "Red", 5 );
    redCirle.Scale( 5.2 );
    std::cout << redCirle;
}

