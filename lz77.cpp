#include "lz77.h"

LZ77::LZ77()
{

}


void LZ77::compress(const QString& string)
{
    reset();

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

            while ((i + j) < pos
                   && (pos + j) < inputSize
                   && string[i + j] == string[pos + j])
            {
                ++j;
            }

            if (j > matchLength)
            {
                matchLength = j;
                matchDistance = pos - i;
            }
        }

        if (matchLength == 0)
        {
            compressedData.append(std::make_tuple(0, 0, string[pos]));
            ++pos;
        }
        else
        {
            qDebug() << pos << matchLength;

            if((pos + matchLength < inputSize))
            {
                compressedData.append(std::make_tuple(matchDistance - 1, matchLength, string[pos + matchLength]));
            }
            else
            {
                if(pos + matchLength != inputSize || matchLength == 1)
                    compressedData.append(std::make_tuple(0, 0, string[pos]));
                else
                    compressedData.append(std::make_tuple(matchDistance - 1, matchLength-1, string[pos + matchLength - 1]));
            }
            pos += matchLength + 1;
        }
    }

}


QVector<std::tuple<QString,QString,QString>> LZ77::visualize()
{
    QVector<std::tuple<QString,QString,QString>> result;
    int32_t index = 0;


    for(const auto& [entrance, length, character]: compressedData)
    {
        result.push_back(std::make_tuple(dict[index],
                                         buffer[index],
                                         "<" + QString::number(entrance) + ", " + QString::number(length) + ", '" + character + "'>"));

        qDebug() << dict[index];
        index++;
    }

    return result;
}

QString LZ77::decompress()
{
    reset();
    QString result;

    for (const auto &entry : compressedData)
    {
        int distance, length;
        QChar nextChar;
        std::tie(distance, length, nextChar) = entry;

        QString currentDictionary = result;
        QString currentBuffer;

        if (distance == 0 && length == 0)
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

void LZ77::parseEncoded(const QString& encodedString)
{
    compressedData.clear();
    qDebug() << encodedString;

    QRegularExpression re("<(\\d+), (\\d+), '([^>]+)'>");
    QRegularExpressionMatchIterator i = re.globalMatch(encodedString);


    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();

        auto entrance = match.captured(1).toInt();
        auto length = match.captured(2).toInt();
        auto character = match.captured(3).at(0);

        compressedData.push_back(std::make_tuple(entrance, length, character));
    }
}


void LZ77::reset()
{
    dict.clear();
    buffer.clear();

}

