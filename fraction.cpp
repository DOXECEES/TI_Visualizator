#include "fraction.h"

Fraction::Fraction(const int32_t num, const int32_t denom)
    : numerator(num)
    , denominator(denom)
{

}


// why the fuck^^^
//Fraction operator+(const Fraction& other)
//{
//    if (denominator == other.denominator)
//    {
//        return Fraction(
//            numerator + other.numerator, denominator
//            );
//    }


//    return
//        Fraction(
//            numerator * other.denominator + denominator * other.numerator,
//            denominator * other.denominator
//            );
//}


/// TODO move realization to cpp from h
