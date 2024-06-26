#ifndef LZSS_H
#define LZSS_H

#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>




#include "ialgorithmlz.h"



class LZSS : public IAlgorithmLZ
{

public:

    LZSS();

    void compress(const QString& string) override;
    QString decompress() override;

    QVector<std::tuple<QString,QString,QString>> visualize() override;
    void parseEncoded(const QString& encodedString) override;

    //inline const QVector<std::tuple<uint8_t, QChar>>& getCompressedData() const { return compressedData;};


private:

    QVector<std::tuple<bool, int, int, QChar>> compressedData;
    QVector<QString> dict;
    QVector<QString> buffer;

};

#endif // LZSS_H
