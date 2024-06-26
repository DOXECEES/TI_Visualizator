#include "lz78.h"

LZ78::LZ78()
{

}


void LZ78::compress(const QString& string)
{
    QHash<QString, uint8_t> dictionary;
    QString currentString;
    int dictSize = 1;

    for (QChar c : string)
    {
        currentString += c;
        if (dictionary.find(currentString) == dictionary.end())
        {
            dictionary[currentString] = dictSize++;
            if (currentString.length() == 1)
            {
                compressedData.push_back(std::make_tuple(static_cast<uint8_t>(0), c ));
            }
            else
            {
                compressedData.push_back({ dictionary[currentString.left(currentString.length() - 1)], c });
            }

            dict.push_back(currentString);
            currentString = "";

        }

    }
    if (!currentString.isEmpty())
    {
        dict.push_back(currentString);
        compressedData.push_back({ dictionary[currentString.left(currentString.length() - 1)], currentString.back() });
    }
}

QVector<std::tuple<QString,QString,QString>> LZ78::visualize()
{
    QVector<std::tuple<QString,QString,QString>> result;
    int32_t indexInTable = 0;

    result.push_back(std::make_tuple(QString::number(0),
                                     "",
                                     ""));

    for(const auto& i: compressedData)
    {
        auto index = std::get<0>(i);
        auto character = std::get<1>(i);

        result.push_back(std::make_tuple(QString::number(indexInTable + 1),
                                        dict[indexInTable],
                                         "<" + QString::number(index) + ", '" + character + "'>"));

        indexInTable++;
    }

    return result;
}

QString LZ78::decompress()
{
    dict.clear();
    dict.resize(1);
    QString decompressedString;

    for (const auto& i : compressedData)
    {
        auto index = std::get<0>(i);
        auto nextChar = std::get<1>(i);
        QString entryString = dict[index] + nextChar;

        decompressedString += entryString;
        dict.push_back(entryString);


    }
    dict.pop_front();

    return decompressedString;
}


void LZ78::parseEncoded(const QString& encodedString)
{
    compressedData.clear();
    qDebug() << encodedString;

    QRegularExpression re("<(\\d+), '([^>]+)'>");
    QRegularExpressionMatchIterator i = re.globalMatch(encodedString);


    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();

        auto index = match.captured(1).toInt();
        auto character = match.captured(2).at(0);
        compressedData.push_back(std::make_tuple(index, character));
    }
}

