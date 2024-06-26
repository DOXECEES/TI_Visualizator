#ifndef LZFACTORY_H
#define LZFACTORY_H

#include <cstdint>

#include "ialgorithmlz.h"

class LZFactory
{

public:

    enum class LZAlgorithm : uint8_t
    {
        LZ77,
        LZSS,
        LZ78,
        LZW
    };

    LZFactory();
    std::unique_ptr<IAlgorithmLZ> create(LZAlgorithm algo);
};

#endif // LZFACTORY_H
