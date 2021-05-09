#include "simplenegot.h"

#include <string>

SimpleNegot::SimpleNegot() {}

void SimpleNegot::writePackage(const Package &data) {
    if(data.size() > 0 && !m_transmitting) {
        packToTransmmit = data;
        packToTransmmit[0].push_back(data.size() - 1);
        m_transmitting = true;
        transmmitPosition = 0;
        recievePosition = std::numeric_limits<decltype (recievePosition)>::max();
        timePoint = 0;
    }
}

SimpleNegot::ByteArray SimpleNegot::proceed(ByteArray input, uint64_t time) {
    if(input.size() > 0) {
        uint8_t id = input[0] & 0x7f;
        if(input[0] & 0x80) {
            transmmitPosition++;
            timePoint = 0;
            if(packToTransmmit.size() - 1 == id) {
                m_transmitting = false;
            }
        } else {
            if(!m_recieving) {
                recievedPack.clear();
                recievePosition = input[input.size() - 1];
                input.resize(input.size() - 1);
                m_recieving = true;
            }
            input.erase(input.begin());
            recievedPack.push_back(input);
            transmmitPosition = id;

            if(id == recievePosition) {
                m_recieving = false;
                f(recievedPack);
            }

            return { static_cast<uint8_t>(id | 0x80) };
        }
    }

    if(m_transmitting && transmmitPosition < packToTransmmit.size() && (time - timePoint) > 1000) {
        timePoint = time;
        auto t = packToTransmmit[transmmitPosition];
        t.insert(t.begin(), transmmitPosition);
        return t;
    }
    return {};
}
