#ifndef SIMPLENEGOT_H
#define SIMPLENEGOT_H

#include <vector>
#include <inttypes.h>
#include <functional>

class SimpleNegot {
    typedef std::vector<uint8_t> ByteArray;
    typedef std::vector<ByteArray> Package;

    Package packToTransmmit;
    bool m_transmitting = false;
    bool m_recieving = false;
    uint8_t transmmitPosition = 0;
    uint8_t recievePosition = 0;
    uint64_t timePoint = 0;

    Package recievedPack;


public:

    std::function<void(Package)> f;

    SimpleNegot();
    void writePackage(const Package &data);
    ByteArray proceed(ByteArray input, uint64_t time);
};

#endif // SIMPLENEGOT_H
