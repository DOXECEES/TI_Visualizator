#include "lzss.h"

LZSS::LZSS()
    :IAlgorithmLZ()
{

}

void LZSS::compress(const QString& string)
{
    int inputSize = string.size();
    int pos = 0;

    while (pos < inputSize)
    {
        int matchLength = 0;
        int matchDistance = 0;

        QString currentDictionary = string.mid(0, pos);
        QString currentBuffer = string.mid(pos, inputSize - pos);

        dict.append(currentDictionary);
        buffer.append(currentBuffer);

        for (int i = pos - 1; i >= 0; --i)
        {
            int j = 0;

            while ((i + j) < pos && (pos + j) < inputSize && string[i + j] == string[pos + j]) {
                ++j;
            }
            if (j > matchLength) {
                matchLength = j;
                matchDistance = pos - i;
            }
        }

        if (matchLength < 1)
        {
            compressedData.append(std::make_tuple(false, 0, 0, string[pos]));
            ++pos;
        }
        else
        {
            QChar nextChar = (pos + matchLength < inputSize) ? string[pos + matchLength] : QChar();
            compressedData.append(std::make_tuple(true, matchDistance - 1, matchLength, nextChar));
            pos += matchLength;
        }
    }

}


QVector<std::tuple<QString,QString,QString>> LZSS::visualize()
{
    QVector<std::tuple<QString,QString,QString>> result;
    int32_t index = 0;


    for(const auto& [flag, entrance, length, character]: compressedData)
    {

        auto code = (flag)
                        ? (QString("1 ") + "<" + QString::number(entrance) + ", " + QString::number(length) +  ">")
                        : (QString("0 '") + character + "'");

        result.push_back(std::make_tuple(dict[index],
                                         buffer[index],
                                         code));

        //qDebug() << dict[index];
        index++;
    }

    return result;
}


QString LZSS::decompress()
{
    QString result;

    for (const auto &entry : compressedData)
    {
        bool isLiteral;
        int distance, length;
        QChar nextChar;
        std::tie(isLiteral, distance, length, nextChar) = entry;

        QString currentDictionary = result;
        QString currentBuffer;

        if (!isLiteral)
        {
            result.append(nextChar);
            currentBuffer = QString(nextChar);
        }
        else
        {
            int startPos = result.size() - distance - 1;
            for (int i = 0; i < length; ++i)
            {
                result.append(result[startPos + i]);
            }
            if (!nextChar.isNull())
            {
                result.append(nextChar);
            }
            currentBuffer = result.mid(startPos, length) + nextChar;
        }

        dict.append(currentDictionary);
        buffer.append(currentBuffer);
    }

    return result;
}


void LZSS::parseEncoded(const QString& encodedString)
{
    compressedData.clear();
    qDebug() << encodedString;

    QRegularExpression re(R"((0 '(.{1})')|(1 <(\d+), (\d+)>))");
    QRegularExpressionMatchIterator i = re.globalMatch(encodedString);


    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();

        if (!match.captured(1).isEmpty())
        {
            compressedData.push_back(std::make_tuple(0, 0, 0, match.captured(2).at(0)));
        }
        else
        {
            compressedData.push_back(std::make_tuple(1, match.captured(4).toInt(), match.captured(5).toInt(), QChar()));
        }

    }
}



