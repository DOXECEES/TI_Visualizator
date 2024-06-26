#include "lzfactory.h"

#include "lz77.h"
#include "lz78.h"
#include "lzss.h"

LZFactory::LZFactory()
{

}

std::unique_ptr<IAlgorithmLZ> LZFactory::create(LZFactory::LZAlgorithm algo)
{

    switch (algo)
    {
        case LZAlgorithm::LZ77:
                return std::make_unique<LZ77>();
        case LZAlgorithm::LZSS:
                return std::make_unique<LZSS>();
        case LZAlgorithm::LZ78:
            return std::make_unique<LZ78>();
        default:
            return {};
    }
}
