#ifndef IALGORITHMLZ_H
#define IALGORITHMLZ_H

#include <QVector>
#include <QPair>
#include <QString>


class IAlgorithmLZ
{
public:
    IAlgorithmLZ();

    virtual void compress(const QString& string) = 0;
    virtual QString decompress() = 0;

    virtual QVector<std::tuple<QString,QString,QString>> visualize() = 0;
    virtual void parseEncoded(const QString& encodedString) = 0;
private:

};

#endif // IALGORITHMLZ_H
