#include "enthropy.h"

Enthropy::Enthropy()
{

}


Enthropy::EnthropyCharacteristics Enthropy::calculate(const QString& str)
{
    if(str.isEmpty())
        return {};

    countOfSymbols = str.size();
    makeFreqTable(str);


    // enthropy
    double enthropy = 0.0;

    for(const auto& i : freqTable)
    {
        enthropy -= (i * std::log2(i));
    }

    //
    double capacity = std::log2(freqTable.size());
    //

    double redundancy = capacity - enthropy;
    double relativeRedundancy = 1 - (enthropy / capacity);


    return EnthropyCharacteristics(enthropy, capacity, redundancy, relativeRedundancy);
}


QString Enthropy::makeStringFraction() const
{
    QString num = "";

    for(const auto& i : fracs)
    {
        num += i.visualize() + "log2( " + i.visualize() + " ) " +  " + ";
    }
    qDebug() << num;
    return num;
}


QVector<QPair<QChar, QString>> Enthropy::visualize()
{
    QVector<QPair<QChar, QString>> res;

    for(const auto& i: order)
    {
        res.push_back({i, QString::number(freqTable[i] * countOfSymbols) +" / " + QString::number(countOfSymbols)});
        fracs.push_back(Fraction(static_cast<int32_t>(freqTable[i] * countOfSymbols),
                                 static_cast<int32_t>(countOfSymbols)));
    }

    return res;
}


void Enthropy::makeFreqTable(const QString& str)
{
    const double freqOfOneUnit = 1 / static_cast<double>(str.size());
    double res = 0;

    for(const auto& i : str)
    {
        freqTable[i] += freqOfOneUnit;


        if(!order.contains(i))
            order.push_back(i);
    }

}
