#ifndef LZ78_H
#define LZ78_H

#include <QVector>
#include <tuple>
#include <QString>
#include <QHash>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


#include "ialgorithmlz.h"


class LZ78 : public IAlgorithmLZ
{
public:
    LZ78();

    void compress(const QString& string) override;
    QString decompress() override;

    QVector<std::tuple<QString,QString,QString>> visualize() override;
    void parseEncoded(const QString& encodedString) override;

    inline const QVector<std::tuple<uint8_t, QChar>>& getCompressedData() const { return compressedData;};


private:

    QVector<std::tuple<uint8_t, QChar>> compressedData;
    QVector<QString> dict;
};

#endif // LZ78_H
