#ifndef FRACTION_H
#define FRACTION_H

#include <QString>

#include <QDebug>

#include <stdint.h>


class Fraction
{
public:
    Fraction() = default;

    Fraction(const int32_t num, const int32_t denom);


    Fraction operator+(Fraction& other)
    {
            if (denominator == other.denominator)
            {
                return Fraction(
                    numerator + other.numerator, denominator
                    );
            }


            return
                Fraction(
                    numerator * other.denominator + denominator * other.numerator,
                    denominator * other.denominator
                    );
    }

    QString visualize() const
    {
            qDebug() << numerator << denominator;
        return QString(QString::number(numerator) + " / " + QString::number(denominator));
    }


    double calculate() const
    {
        return static_cast<double>(static_cast<double>(numerator) / static_cast<double>(denominator));
    }


private:

    int32_t numerator = 0;
    int32_t denominator = 1;
};

#endif // FRACTION_H
