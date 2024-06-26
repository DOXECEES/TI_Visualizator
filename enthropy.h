#ifndef ENTHROPY_H
#define ENTHROPY_H

#include <QChar>
#include <QHash>
#include <qdebug.h>
#include <QVector>
#include <QString>
#include <QPair>
#include <QtMath>

#include "fraction.h"

class Enthropy
{
public:

    struct EnthropyCharacteristics
    {
        EnthropyCharacteristics() = default;

        EnthropyCharacteristics(double e, double c, double r, double rr)
            : enthropy(e)
            , capacity(c)
            , redundancy(r)
            , relativeRedundancy(rr)
        {}

        double enthropy = 0.0;
        double capacity = 0.0;
        double redundancy = 0.0;
        double relativeRedundancy = 0.0;

    };


    Enthropy();

    EnthropyCharacteristics calculate(const QString& str);

    QVector<QPair<QChar, QString>> visualize();

    QString makeStringFraction() const;

private:

    void makeFreqTable(const QString& str);

    QHash<QChar, double> freqTable;
    QVector<QChar> order;
    QVector<Fraction> fracs;
    double countOfSymbols = 0;


};

#endif // ENTHROPY_H
