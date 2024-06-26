#ifndef LZ77_H
#define LZ77_H

#include <QString>
#include <QHash>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "ialgorithmlz.h"

class LZ77 : public IAlgorithmLZ
{
public:

    LZ77();

    void compress(const QString& string) override;
    QString decompress() override;

    QVector<std::tuple<QString,QString,QString>> visualize() override;
    void parseEncoded(const QString& encodedString) override;

    void reset();

private:

    QVector<std::tuple<int32_t, int32_t, QChar>> compressedData;
    QVector<QString> dict;
    QVector<QString> buffer;
};

#endif // LZ77_H
